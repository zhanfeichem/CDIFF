#ifndef DL_FDM
#define DL_FDM
using namespace std;
//CPP header
#include <iostream>
#include <fstream>
#include<sstream>
#include<vector>
#include<map>
#include <string>
//boost header
#include<boost/tokenizer.hpp>//�ָ��ַ���
//#include<boost/lexical_cast.hpp>//ת������
#include<boost/format.hpp>//��ʽ�����
//C header
#include<stdlib.h>//ʹ��exit()
#include<math.h>//ʹ�����Ǻ���
#include <string.h>//c����ַ�������
#include<time.h> //ʱ�������������
#include<stdlib.h>
#include <unistd.h>//�л�����Ŀ¼ _acess����
#include <setjmp.h>
#include<signal.h>
#include <sys/stat.h>//mkdir����
#include <sys/types.h>//mkdir����
//#include<sys/wait.h>
//My header


#include "subfdmdiff.hpp"//����� ��ʱ����
using namespace fdmdiff;
#include "subfdm.hpp"
using namespace fdm;
//
#include "mytool.hpp"
#include "glo.hpp"
#include "read_dat.hpp"//read_fdm
double dl_mycfit_fdm(int ,double* );
//int fdminp(vector<PDB> pdbline);
//int fdmnesinp(vector<PDB> pdbline,char workdir_char[CHAR_LEN]);//ʹ��runfdm�еİ汾
double dl_save(int npar,double* x);

double dl_mycfit_fdm(int npar,double* x){
//char mycom[CHAR_LEN];//����shell�����ô�ִ�� �ǵ�ÿ�����
double result = 1e21;
vector<PDB> pdbline;
getpdb(pdbline);

//�ı伸�β���
change_shell_ini(pdbline);

//int n_change=1;
//change_shell(n_change,'B',x[0],pdbline);
//change_shell(n_change,'C',x[1],pdbline);
//change_shell(n_change,'D',x[1],pdbline);
//change_shell(n_change,'E',x[2],pdbline);
//change_shell(n_change,'F',x[2],pdbline);
//�ı伸�β���

//double atom2[3]={0.859,-1.195,1.404};
//double atom3[3]={0.275,-1.726,-1.219};
//double atom4[3]={-1.949,-0.467,0.667};
//double atom5[3]={1.918,0.774,-0.430};
//double atom6[3]={-0.053,1.489,1.507};
//int n_change=0;
//double chang1[3]={x[0],0.0,0.0};
//double chang2[3]={x[1],0.0,0.0};
//double chang3[3]={x[2],0.0,0.0};
////bpy axis
//change_lig(n_change,'B',chang1,atom2,pdbline);
////bpy plane
//change_lig(n_change,'C',chang2,atom3,pdbline);
////dpa
//change_lig(n_change,'D',chang3,atom4,pdbline);
//change_lig(n_change,'E',chang3,atom5,pdbline);
//change_lig(n_change,'F',chang3,atom6,pdbline);
if(myinput.geom_model==1){
int n_change=myinput.geom_ngroup;

for(int i=0;i<myinput.geom_n;i++){
        int nn=myinput.geom_xi[i];
        double change[3]={x[nn],0,0};
        double atom[3]={myinput.geom_atom[i][0],myinput.geom_atom[i][1],myinput.geom_atom[i][2]};
        change_lig(n_change,myinput.geom_group[i],change,atom,pdbline);
}//end for

}//end if
else if(myinput.geom_model==11){
int n_change=myinput.geom_ngroup;

for(int i=0;i<myinput.geom_n;i++){

        int nn=myinput.geom_xi[i];

        double change[3]={x[nn],0,0};

        //cout<<"dr  "<<change[0]<<" dtheta "<<change[1]<<" dphi "<<change[2]<<endl;
        double atom[3]={myinput.geom_atom[i][0],myinput.geom_atom[i][1],myinput.geom_atom[i][2]};
        change_lig_val(n_change,myinput.geom_group[i],change,atom,pdbline);
}//end for

}//end else11

else if(myinput.geom_model==2){
int n_change=myinput.geom_ngroup;
for(int i=0;i<myinput.geom_n;i++){
        int ri=myinput.geom_r[i];
        int thetai=myinput.geom_theta[i];
        int phii=myinput.geom_phi[i];
        //
        double change[3]={x[ri],x[thetai],x[phii]};
        //cout<<"r theta phi"<<x[ri]<<x[thetai]<<x[phii]<<endl;
        //cout<<"dr  "<<change[0]<<" dtheta "<<change[1]<<" dphi "<<change[2]<<endl;
        double atom[3]={myinput.geom_atom[i][0],myinput.geom_atom[i][1],myinput.geom_atom[i][2]};
        change_lig_val(n_change,myinput.geom_group[i],change,atom,pdbline);
}//end for

}//end else





//���pdb
save_pdb(pdbline,npar,x);
//�����ļ���
char workdir_char[CHAR_LEN];
//myworkdir(workdir_char);//���������ַ��� ��Ϊ����Ŀ¼
//fdmnesʹ�ù̶��ļ���
strcpy(workdir_char,"fdmnesrun");
//feffinp
//feffinp(pdbline);
fdmnesinp(pdbline,workdir_char);//����Ŀ¼�½���feffinp
//debug

//����feff
//�����������ڲ�����Ŀ¼ ��ȡ�������нű���ָ���ļ���  ��������fdmnes��δ�����
char dirnow_char[CHAR_LEN];//���浱ǰĿ¼�Ա㷵��
getcwd(dirnow_char,sizeof(dirnow_char));
chdir(workdir_char);//����ı�Ŀ¼��if setjnp֮ǰ���޷�ɾ������Ŀ¼ ��Ϊʹ�õ������·�� ��ǰĿ¼����

//����fdmnes��Ҫ�ļ�  �����ļ�����

if(myinput.runCore==1)system(myinput.fdmneswin);


//���в��ֽ���
chdir(dirnow_char);//������Ŀ¼������Ŀ¼
//�ж�xmu.dat�Ƿ����
char xmupos_char[CHAR_LEN];
memcpy(xmupos_char,workdir_char,CHAR_LEN);
strcat(xmupos_char,"/out.txt");//����ļ���
if(access(xmupos_char,0)==-1) {

//        char rm_char[CHAR_LEN]=RMDIR;//given blank in the edn of the commad
//
//        strcat(rm_char,workdir_char);
//
//        system(rm_char);
        result=1e22;
        wrongfile("saveall",x,npar,"noxmu");
        remove("./fdmnesrun/out.bk");
        remove("./fdmnesrun/out_conv.bk");
        return result;
}//if block ends

//���νṹ��������ȫ�ֱ���mypar�ṹ��
myinput.fdm_ngeom=npar;
//myinput.pargeom=(double *)malloc(mypar.ngeom*sizeof(double));
myinput.fdm_pargeom=vector<double>(npar);
for(int i=0;i<npar;i++)myinput.fdm_pargeom[i]=x[i];

//����ѵ�����ݼ�
dl_save(npar,x);
//
remove("./fdmnesrun/out.bk");
remove("./fdmnesrun/out_conv.bk");
rename("./fdmnesrun/out.txt","./fdmnesrun/out.bk");
rename("./fdmnesrun/out_conv.txt","./fdmnesrun/out_conv.bk");
//return result;
return 0;


}//end of mycfit��������




double dl_save(int npar,double* x){
    vector<vector<double> > dat_xmu;
    vector<double> x_xmu,y_xmu;
    //���ļ���ȡ����
    read_dat_fdm("fdmnesrun/out_conv.txt",2,dat_xmu);//�򿪾����
    x_xmu=dat_xmu[0];y_xmu=dat_xmu[1];

    //���ݱ���
    ofstream dlsave("dl_spc.txt",ios::app);
    for(unsigned i=0;i<=y_xmu.size()-1;++i)
       dlsave<<boost::format("%15.8f")%(y_xmu[i]);
    dlsave<<endl;//�����׽���
    //�������
    ofstream dlpar("dl_par.txt",ios::app);
    for(unsigned i=0;i<npar;i++){
        dlpar<<x[i]<<" ";
        std::cout<<x[i]<<"  ";
    }
    dlpar<<endl;
    cout<<endl;

}













#endif // DL_FDM

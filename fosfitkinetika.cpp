/*
 * fosfitkinetika.cpp
 *
 *  Created on: 13.12.2014
 *      Author: Celvins
 */

#include "fosfitkinetika.h"
#include <iostream>
#include <math.h>
using namespace std;
double F_SUM(double * ko)
	{
		double C[4][2],nKlast[2];		//koncentracii komponentov A1-A4 bezrazmernie, 4islo klasterov
		double C3_ravn,C1R,C2R,C3R,C4R;// ravnovesnaya koncentraciya A3, razmernie koncentracii A1-A4
		double C0,K1,K0,G1,G2,G3,G4,DT,J;
		double VQ,V0,VPR,R03,R0,NKR;
		double B1,B2,B3,NZ0,NZR,S,SB,L0;
		double M0,N0,NU0,K00,LLR,MKR,M1,M2;
		double M_SOL;
		double C1O,C2O;
		double C1OR,C2OR,VQR,VR,VPRR,DTR,TAUR,TAU,R03R,R0R,K1R,K0R,B1R,B2R,B3R;
		double K10,KK0,B10,B20,B30,C3_ravnR,VQ0,T0,R030,R00,V00,VV, F ;
		double SN;
		double N[2][3010],NU[2][3010];
		double L_exp,M_exp,C1_exp,C2_exp,C3_exp;
		int i,DK,NK,k,NumberOfFile;
		DK=1;KK0=7980; B30=1;i=0; LLR=0;
		K1R=ko[0];
		K0R=ko[1];
		B1R=ko[2];
		B2R=ko[3];
		B3R=ko[4];
		//FILE *failik;
		FILE *file2;
		F =0.0;
	// peremennie iz faila//
		for(NumberOfFile=0;NumberOfFile<2;NumberOfFile++)
		{
			if(NumberOfFile==0)
				if((file2 = fopen("input1.txt", "r")) == 0)
					cout << "error file 1";
			else
				if((file2 = fopen("input2.txt", "r")) == 0)
					cout << "error file 2";
			fscanf(file2,"%lf\n",&VQR);
			fscanf(file2,"%lf\n",&VR);
			fscanf(file2,"%lf\n",&VPRR);
			fscanf(file2,"%lf\n",&DTR);
			fscanf(file2,"%lf\n",&TAUR);
			fscanf(file2,"%lf\n",&C1OR);
			fscanf(file2,"%lf\n",&C2OR);
			fscanf(file2,"%lf\n",&C3_ravnR);
			fscanf(file2,"%lf\n",&R03R);
			fscanf(file2,"%lf\n",&R0R);
			fscanf(file2,"%lf\n",&G1);
			fscanf(file2,"%lf\n",&G2);
			fscanf(file2,"%lf\n",&G3);
			fscanf(file2,"%lf\n",&G4);
			fscanf(file2,"%lf\n",&NKR);
			fscanf(file2,"%lf\n",&VQ0);
			fscanf(file2,"%lf\n",&T0);
			fscanf(file2,"%lf\n",&C0);
			fscanf(file2,"%lf\n",&R030);
			fscanf(file2,"%lf\n",&R00);
			fscanf(file2,"%lf\n",&L_exp);
			fscanf(file2,"%lf\n",&M_exp);
			fscanf(file2,"%lf\n",&C1_exp);
			fscanf(file2,"%lf\n",&C2_exp);
			fscanf(file2,"%lf",&C3_exp);
			fclose(file2);
//Obezrazmerivanie vhodnih dannih//
			C1O=C1OR/C0;
			C2O=C2OR/C0;

			C3_ravn=C3_ravnR/C0;
			DT=DTR/T0;

			TAU=TAUR/T0;
			VQ=VQR/VQ0;

			V00=VQ0*T0/3600;
			V0=VR/V00;

			VPR=VPRR/V00;
			K10=1/(C0*T0);

			K00=C0/(R030*R00*T0);
			NZ0=K00*T0;

			B10=1/(NZ0*T0);
			B20=B10;

			NU0=pow(KK0,B30)*B20*NZ0;
			N0=NZ0/(NU0*KK0*T0);

			R03=R03R/R030;
			R0=R0R/R00;

			K1=K1R/K10;
			K0=K0R/K00;

			B1=B1R/B10;
			B2=B2R/B20;

			B3=B3R/B30;
			NK=int(NKR/KK0);

			L0=pow(KK0*R00,0.3333);
			M0=R030*R00*pow(KK0,2)*N0;

//obnylenie massivov//
			J=0.;
			S=0.0;

			for(k=0; k<NK; k++)
			{
				NU[0][k]=0.;	//!skorost' rosta kristallov
				N[0][k]=0.;		//!Chislo kristallov
			}
			nKlast[0]=0. ;		//!Chislo klasterov
			C[0][0]=C1O;		//koncentraciya komponenta 1
			C[1][0]=0.0 ;		//koncentraciya komponenta 2
			C[2][0]=0.0 ;		//koncentraciya komponenta 3
			C[3][0]=0.0;		//koncentraciya komponenta 4

////progonyem cikl po vremeni//
			while( J < ( TAU - DT))
			{
//s4itaem C1
				C[0][1]=C[0][0]*(1-K1*G1*DT*C[1][0]);
				C1R=C[0][1]*C0;
//s4itaem C2
				if(J>VPR/VQ )
				{
					C[1][1]=C[1][0]*(1-K1*G2*DT*C[0][0]);
					VV=V0+VPR;
					M1=V0*V00*(1.0e-3)*C1OR;
					M2=VPR*V00*(1.0e-3)*C2OR;
				}
				else
				{
					C[1][1]=(VQ*C2O*DT)/(V0+J*VQ)+C[1][0]*(1-K1*G2*DT*C[0][0]);
					VV=V0+J*VQ;
					M1=V0*V00*(1.0e-3)*C1OR;
					M2=J*VQ*V00*(1.0e-3)*C2OR;
				}
				M_SOL=M1+M2;
				C2R=C[1][1]*C0;
//s4itaem C3
				if(C[2][0]<C3_ravn)
					C[2][1]=C[2][0]+K1*G3*DT*C[0][0]*C[1][0];
				else
					C[2][1]=C[2][0]+K1*G3*DT*C[0][0]*C[1][0]-R03*K0*R0*DT*((C[2][0]-C3_ravn)/C3_ravn)*((C[2][0]-C3_ravn)/C3_ravn);
				if(C[2][1]<0)
				{
					C3R=C3_ravnR;
					C[2][1]=C3R/C0;
				}
				else
				{
					C3R=C[2][1]*C0;
				}
//s4itaem C4
				C[3][1]=C[3][0]+K1*G4*C[0][0]*C[1][0]*DT;
				C4R=C[3][1]*C0;
///massa kristallov//
				MKR=M_SOL-VV*V00*(1.0e-3)*(C1R+C2R+C3R+C4R);
				if(MKR<0.0)
					MKR=0.0;
//!	Rasschet chisla ultramicrocristallov
				if(C[2][0]<C3_ravn)		///esli tekywaya koncentraciya menwe ravnovesnoi
					nKlast[1]=nKlast[0]-DT*(B1*nKlast[0]*nKlast[0]+S);
				else
					nKlast[1]=nKlast[0]+DT*(K0*((C[2][0]-C3_ravn)/C3_ravn)*((C[2][0]-C3_ravn)/C3_ravn)-B1*nKlast[0]*nKlast[0]-S);

				if(nKlast[1]<0)
					{
					NZR=1.e10;
					nKlast[1]=NZR/NZ0;
					}
				else
					NZR=nKlast[1]*NZ0;
///!	Raschet lineinoi skorosti rosta kristallov
				S=0.0;
				SN=0.0;
				SB=0.0;
				NU[1][0]=B2*pow(0.00025,B3)*nKlast[1];
				N[1][0]=B1*pow(nKlast[1],2)/(0.00025)*NU[1][0];

				for(k=1;k<3001; k++)
				{
					NU[1][k]=B2*nKlast[1]*pow(k,B3);
//!	Rasschet chisla chastic
					N[1][k]=((N[1][k-1]*NU[1][k-1]*DT/DK)+N[0][k])/(1+NU[1][k]*DT/DK);
					S=S+N[1][k]*NU[1][k]*DK;	// !Summa N(j,k)*NU(j,k)*dk
					SB=SB+k*N[1][k]*DK;			//  !Summa k*N(j,k)*dk
					SN=SN+N[1][k]*DK ;			//  !Summa N(j,k)*dk, SN- obshee chislo krystallov
					N[0][k]=N[1][k];
				} //for(k=0;k<3000; k++)
//srednii razmer kristallov////////////////////////////////////////////////////////////////////////////
				if(SN>=1.e-30)
					LLR=pow((6.0*(SB/SN)*R0/3.14),0.333)*L0;	//  !LLR - sredniy razmer krystallov

				J=J+DT;
				nKlast[0]=nKlast[1];
				C[0][0]=C[0][1];
				C[1][0]=C[1][1];
				C[2][0]=C[2][1];
				C[3][0]=C[3][1];
			}///while(J<TAU)
		}
		F =F+pow((LLR-L_exp)/L_exp,2)+pow((MKR-M_exp)/M_exp,2)+pow((C1R-C1_exp)/C1_exp,2)+pow((C2R-C2_exp)/C2_exp,2)+pow((C3R-C3_exp)/C3_exp,2);
		return F;
	}
/* namespace s */

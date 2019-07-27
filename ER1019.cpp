#include<iostream>
#include<ctime>
#include<time.h>
#include<map>
#include<set>
#include<list>
#include<vector>
#include<fstream>
#include<stdlib.h>
#include<stdio.h>
#include<algorithm>
#include<iomanip>
#include<cmath>
#include <functional>
#include <numeric>
using namespace std;


////////////////////////////////////////////////////////////////////////////the begin of the random number function
// get the better random number 
#include <stdio.h>
#undef N
#undef M
#define N 25
#define M 7

static unsigned int tt800_state[N]={ /* default initial 25 seeds, change as you wish */
  0x95f24dab, 0x0b685215, 0xe76ccae7, 0xaf3ec239, 0x715fad23,
  0x24a590ad, 0x69e4b5ef, 0xbf456141, 0x96bc1b7b, 0xa7bdf825,
  0xc1de75b7, 0x8858a9c9, 0x2da87693, 0xb657f9dd, 0xffdc8a9f,
  0x8121da71, 0x8b823ecb, 0x885d05f5, 0x4e20cd47, 0x5a9ad5d9,
  0x512c0c03, 0xea857ccd, 0x4cc1d30f, 0x8891a8a1, 0xa6b7aadb
};


/* initial with any value */
void tt800_seed(unsigned int seed)
{
  tt800_state[0] = seed;
  int i;
  for (i=1; i<N; i++){
    tt800_state[i] = 69069 * tt800_state[i-1];
  }
}




/* generate a 32 bit unsigned integer on [0, 0x100000000) */
unsigned int
tt800_int32(void)
{
  unsigned int ret, temp;
  static int k = 0;
  static unsigned int mag01[2]={ 
    0x0, 0x8ebfd028 /* this is magic vector `a', don't change */
  };
  
  if (k==N) { /* generate N words at one time */
    int kk;
    for (kk=0; kk<N-M; kk++) {
      temp = (tt800_state[kk] >> 1) ^ mag01[tt800_state[kk] % 2];
      tt800_state[kk] = tt800_state[kk+M] ^ temp;
    }
    for (; kk<N; kk++) {
      temp = (tt800_state[kk] >> 1) ^ mag01[tt800_state[kk] % 2];
      tt800_state[kk] = tt800_state[kk+(M-N)] ^ temp;
    }
    k=0;
  }
  ret = tt800_state[k];
  ret ^= (ret << 7) & 0x2b5b2500; /* s and b, magic vectors */
  ret ^= (ret << 15) & 0xdb8b0000; /* t and c, magic vectors */
  ret &= 0xffffffff; /* you may delete this line if word size = 32 */
  /* 
     the following line was added by Makoto Matsumoto in the 1996 version
     to improve lower bit's corellation.
     Delete this line to o use the code published in 1994.
  */
  ret ^= (ret >> 16); /* added to the 1994 version */
  k++;
  return ret;
}


/* 24 bit single real number on [0, 1]*/
float
tt800_single(void)
{
  return (tt800_int32() & 0xffffff) / (float)0xffffff ;
}


/* generates a random number on (0,1) with 53-bit resolution*/
double
tt800_double(void)
{
  unsigned int a = tt800_int32() >> 5, b = tt800_int32() >> 6;
  return(a * 67108864.0 + (b | 1)) * (1.0 / 9007199254740992.0);
}
#undef N
#undef M

///////////////////////////////////////////////////////////////////////////////////////// the end of the random number function 
#define N         1000
#define K         10000//the <k> is 2K/N
#define Species   1
#define Capacity   1
#define PN         0.2  //the probability of introduing new species
#define PA        1     // the probability of accepting this new species

#define runtime   1000000 
#define steptime   500
#define startime     5000
#define repit  20

int main()
{
  
  double start=clock();
  
  typedef multimap<int,int> nodes;
  nodes Net;
  nodes UNet;    
  nodes::const_iterator  Mapiter;
  

  
  typedef multimap<int,int> MemeNum;    
  MemeNum tempmeme;
  MemeNum TypeAge; 
  MemeNum::const_iterator Memtre;
  
    
  typedef map<int , int> Typenum;
  Typenum::iterator  mapter;
  
  
  vector<int> neispread;
  vector<int>  MemeEvo;
  vector<int> MemeEvoNum;
  vector<int>  ChoseNodeNeighbor;

  
  vector<int> killnptype;
 

  vector<int>  *MemoryNum;
  MemoryNum =new vector<int>[N];
  
  vector<int>  *MemoryType;
  MemoryType =new vector<int>[N];
  
  vector<int>  *MemoryAge;
  MemoryAge =new vector<int>[N];
  
  
  vector<int>::iterator vtr;
  
  
  ofstream test("infor.txt");
  ofstream ER("RandomNet.txt",ios::trunc);
  
  ofstream MemeNumfile("1MemeNumEvo.txt" ,  ios::out); 
  ofstream LifeTimefile("2LifeTime.txt",  ios::out); 
  ofstream Abundancefile32("32Popu.txt",  ios::out); 
  ofstream Abundancefile311("311SysAbu.txt",  ios::out); 
  ofstream degree("Degree.txt");
  
  tt800_seed(time(0));
  
  for (int Repit=0;  Repit< repit ; Repit++   )
    {	
      	
      
      Net.clear();
      UNet.clear();
      MemeEvo.clear();
      
         
      
      for (int i=0;i<N;i++)
        {
	      MemoryNum[i].clear();
	      MemoryType[i].clear();
	      MemoryAge[i].clear();
        }        
      ///////////////////////////////////1.build the ER net
      
      for(int i=1; i<N;i++)
	{
	  Net.insert(nodes::value_type( i,i-1 ) ); 
	}
      
      while(Net.size()<K)
	{          
	  int  n1=tt800_int32()%N;
	  int  n2=tt800_int32()%N;
	  
	  if ( n1!=n2 )
	    {
	      int countredunce=0;
	      for( Mapiter=Net.begin(); Mapiter!=Net.end(); Mapiter++ )
		{
		  if(  ( Mapiter->first==n1 && Mapiter->second==n2) ||  (Mapiter->first==n2 && Mapiter->second==n1)  )
		    {
		      countredunce=countredunce+1;
		    }
		}
	      if(countredunce==0)
		{
		  Net.insert( nodes::value_type(n1, n2));
		}
	    }	  
	}
      
      
      
      for( Mapiter=Net.begin(); Mapiter!=Net.end(); Mapiter++ )
	{
	  ER<<Mapiter->first<<setw(10)<<Mapiter->second<<endl;
	  UNet.insert( nodes::value_type(Mapiter->first,Mapiter->second ));
	  UNet.insert( nodes::value_type(Mapiter->second,Mapiter->first ));  
	}
      ER<<"-1   "<<setw(10)<<"  -1  "<<endl;
      
      
      test<<"!!!!!!!!!!!!!!!!!!!!!!the initial netsiz is  "<<Net.size()<<endl;
      
      cout<<"Net is OK    "<<Repit<<endl;
      
      ///////////////////////////////////////////part2 the rule of update  on net////////////////////////////////////
      //initial the state of the net      
      for (int i=0;i<N;i++)
	{
	  for (int j=0;j<Species;j++)
	    {
	      MemoryNum[i].push_back(Capacity/Species);
	      MemoryType[i].push_back( tt800_int32() );
	      MemoryAge[i].push_back(1);
	    }
	} 

      ////////////////////////////////////////evolution start////////////////////////////////////////
      for (int time=0;time<runtime;time++)
	{
	  //cout<<"time  is "<<time<<"   @@  for  "<<Repit<<endl;
	  
	  int Turn=0;
	  //1. creative one new species with PN, and spread it, otherwise, chose one and spread it.      
	  int  chosenode=tt800_int32()%N;   //  chosenode to spread   
	  int SpreadNp=0;
	  int SpreadP=0;
	  int SpreadAgeNp=0;

        
	  if ( tt800_single( ) <PN   )  //with PN spread new one type
	    { 
	      Turn=0;
	      int choseindividualkill=tt800_int32()%Capacity+1;
	      int killtype=0;
	      int countnum=0;
	      
	      for (int i=0;i<MemoryNum[chosenode].size();i++ )
		{
		  countnum=countnum+MemoryNum[chosenode][i];
		  if (  choseindividualkill<=countnum    )
		    {
		      killtype=i;
		      break;
		    }
		}
	      int typep=MemoryType[chosenode][killtype];
	      MemoryNum[chosenode][killtype]=MemoryNum[chosenode][killtype]-1;   //kill one !!!!! 
	      int typepage=MemoryAge[chosenode][killtype];
	      if (  MemoryNum[chosenode][killtype]==0   )  
		{
		  MemoryAge[chosenode][killtype]=0;            
		  MemoryNum[chosenode].erase( MemoryNum[chosenode].begin()+killtype  );
		  MemoryAge[chosenode].erase( MemoryAge[chosenode].begin()+killtype  );
		  MemoryType[chosenode].erase( MemoryType[chosenode].begin()+killtype  );     
		}
	      
	      MemeEvo.clear();
	      for (int i=0; i<N;i++)
		{
		  for ( int j=0; j<MemoryNum[i].size(); j++ )
		    {
		      MemeEvo.push_back( MemoryType[i][j] );
		    }
		}
	      
	      sort( MemeEvo.begin(), MemeEvo.end() );
	      MemeEvo.erase( unique(MemeEvo.begin(), MemeEvo.end()), MemeEvo.end() );  //get the unique all atoms
	      
	      if (  find(MemeEvo.begin(), MemeEvo.end(), typep)==MemeEvo.end()  &&  time >startime)
		{
		  LifeTimefile<<typepage<<endl;
		}
	      
	      int SpreadTypeP=tt800_int32();
	      vtr=find(MemeEvo.begin(), MemeEvo.end(), SpreadTypeP); 
	      while(    vtr!=MemeEvo.end()  )//
		{
		  SpreadTypeP=tt800_int32() ;
		  vtr=find(MemeEvo.begin(), MemeEvo.end(), SpreadTypeP);
		}  
	      MemoryNum[chosenode].push_back(1);
	      MemoryType[chosenode].push_back(SpreadTypeP);
	      MemoryAge[chosenode].push_back(1);
 	      SpreadP=SpreadTypeP;	
	    }//end of  if
	  else // with 1-PN spread one already existed type
	    {
	      Turn=1;
	      int choseindividualcopy=tt800_int32()%Capacity+1; 
	      
	      int countnum1=0;
	      for (int i=0;i<MemoryNum[chosenode].size();i++ )        
		{
		  countnum1=countnum1+MemoryNum[chosenode][i];
		  if ( choseindividualcopy<=countnum1  )
		    {
		      SpreadNp=MemoryType[chosenode][i]; 
		      SpreadAgeNp=MemoryAge[chosenode][i];  
		      break;
		    }
		}
	    }
	  
	  
	  killnptype.clear();
	  neispread.clear();
          TypeAge.clear();
	  if( Turn==1 )
	    {    
	      
	      //2. the neighbour accept the meme from the chosen node with probability PA
	      ChoseNodeNeighbor.clear();
	      pair<nodes::iterator, nodes::iterator> itp=UNet.equal_range( chosenode );  // get the neighbor of the chosenode
	      
	      for (Mapiter=itp.first; Mapiter!=itp.second; Mapiter++  )
		{
		  ChoseNodeNeighbor.push_back( (*Mapiter).second );
		}
	      
	      sort(  ChoseNodeNeighbor.begin(),  ChoseNodeNeighbor.end() );
	      ChoseNodeNeighbor.erase( unique( ChoseNodeNeighbor.begin(),  ChoseNodeNeighbor.end()),  ChoseNodeNeighbor.end() );  //get the unique all atoms
	      
	      
	      degree<<ChoseNodeNeighbor.size() <<endl;
	      for ( int  checknodei=0; checknodei<ChoseNodeNeighbor.size(); checknodei++  )  
		{
		  
		  int checknode=ChoseNodeNeighbor[checknodei];
		  //a. empty one 
		  int choseindividualreplace=tt800_int32()%Capacity+1;
		  int countnum=0;
		  int replacetype=0;
		  for (int j=0; j<MemoryNum[ChoseNodeNeighbor[checknodei]].size(); j++)
		    {
		      countnum=countnum+MemoryNum[ChoseNodeNeighbor[checknodei]][j];
		      if (  choseindividualreplace<=countnum )
			{
			  replacetype=j;
			  break;
			}
		    }
		  
		  MemoryNum[ ChoseNodeNeighbor[checknodei]][replacetype]=MemoryNum[ ChoseNodeNeighbor[checknodei] ][replacetype]-1;
		  killnptype.push_back(  MemoryType[ ChoseNodeNeighbor[checknodei]][replacetype]  );
		  if ( MemoryNum[ ChoseNodeNeighbor[checknodei] ][replacetype]==0  )
		    { 
		      TypeAge.insert(  MemeNum::value_type(  MemoryType[ ChoseNodeNeighbor[checknodei]][replacetype], MemoryAge[ChoseNodeNeighbor[checknodei]][replacetype]    ) ); 
		      MemoryAge[ ChoseNodeNeighbor[checknodei] ][replacetype]=0;
		      MemoryAge[ ChoseNodeNeighbor[checknodei] ].erase( MemoryAge[ ChoseNodeNeighbor[checknodei] ].begin()+replacetype   );
		      MemoryNum[ ChoseNodeNeighbor[checknodei]].erase( MemoryNum[ ChoseNodeNeighbor[checknodei]].begin()+replacetype   );
		      MemoryType[ ChoseNodeNeighbor[checknodei]].erase( MemoryType[ ChoseNodeNeighbor[checknodei]].begin()+replacetype   ); 
		    }
		  
		  // b. accept the SpreadType one node by one
		  vtr=find(  MemoryType[ChoseNodeNeighbor[checknodei]].begin(),  MemoryType[ChoseNodeNeighbor[checknodei]].end(), SpreadNp ); //only return the first element,but not the others!!!!@
		  
		  
		  if (   vtr!=MemoryType[ChoseNodeNeighbor[checknodei]].end() )
		    {
		      MemoryNum[ChoseNodeNeighbor[checknodei]][ vtr-MemoryType[ChoseNodeNeighbor[checknodei]].begin()  ]=MemoryNum[ChoseNodeNeighbor[checknodei]][ vtr-MemoryType[ChoseNodeNeighbor[checknodei]].begin()]+1; 
		      //		      SpreadAgeNp.push_back(  MemoryAge[ChoseNodeNeighbor[checknodei]][ vtr-MemoryType[ChoseNodeNeighbor[checknodei]].begin()  ]);
		      MemoryAge[ChoseNodeNeighbor[checknodei]][ vtr-MemoryType[ChoseNodeNeighbor[checknodei]].begin()  ]= SpreadAgeNp;
		    }
		  else
		    {
		      MemoryNum[ChoseNodeNeighbor[checknodei]].push_back(1);
		      MemoryType[ChoseNodeNeighbor[checknodei]].push_back(SpreadNp);
		      MemoryAge[ChoseNodeNeighbor[checknodei]].push_back( SpreadAgeNp  );
		    } 
		  
		  MemeEvo.clear();
		  for (int i=0; i<N;i++)
		    {
		      for ( int j=0; j<MemoryNum[i].size(); j++ )
			{
			  MemeEvo.push_back( MemoryType[i][j] );
			}
		    }
		  
		  sort( MemeEvo.begin(), MemeEvo.end() );
		  MemeEvo.erase( unique(MemeEvo.begin(), MemeEvo.end()), MemeEvo.end() );  //get the unique all atoms
		  

		  for ( int i=0; i<killnptype.size();  i++  )
		    {
		      if (  find(MemeEvo.begin(), MemeEvo.end(), killnptype[i])==MemeEvo.end()  &&  time >startime)
			{
                
			   LifeTimefile<<(TypeAge.find( killnptype[i] ))->second <<endl;
			}
		    }
		  
		}//for all search the neighbors
	      
	      
	    }//if Turn==1
	  
	  
	  
	  //get the result file 1.evolution of number 
	  MemeEvo.clear();
	  if ( Turn==1 )
	    {  
	      for (int i=0;i<N;i++ )
		{
		  for (int j=0;j<MemoryNum[i].size(); j++)
		    {
		      if (  MemoryNum[i][j] !=0  )
			{ 
			  MemoryAge[i][j]=MemoryAge[i][j]+1;
			  MemeEvo.push_back( MemoryType[i][j]);    
			}
		    }
		} 
	    }
	  
	  if ( Turn==0 )
	    {
	      for (int i=0;i<N;i++ )
		{
		  for (int j=0;j<MemoryNum[i].size(); j++)
		    {
		      //TypeAge.insert(MemeNum::value_type( MemoryType[i][j]  ,  MemoryAge[i][j]  ));
		       MemeEvo.push_back( MemoryType[i][j]);    
		      if (  MemoryNum[i][j] !=0   &&  i!= chosenode )  
			{ 
			  MemoryAge[i][j]=MemoryAge[i][j]+1;
			}
		      if ( MemoryNum[i][j]!=0  && i== chosenode )
			{
			  if (  MemoryType[i][j] != SpreadP  )
			    {
			      MemoryAge[i][j]=MemoryAge[i][j]+1;
			    }
			}
		    } 
		}
	    }
  
        
        
	  sort( MemeEvo.begin(), MemeEvo.end() );
	  MemeEvo.erase( unique(MemeEvo.begin(), MemeEvo.end()), MemeEvo.end() );  //get the unique all atoms
	  MemeEvoNum.push_back(MemeEvo.size() );
	  MemeNumfile<<MemeEvo.size()<<endl;
	 
	   


        
	  //2. abundance distribution
 
	  tempmeme.clear();
	  if (time%steptime==0 && time>startime)  //
	    {
	      for( int j=0; j<N; j++)
		{
		  for ( int k=0;k<MemoryNum[j].size(); k++ )
		    {
		      if( MemoryNum[j][k]!=0  )
			{ 
			  tempmeme.insert( MemeNum::value_type( MemoryType[j][k], MemoryNum[j][k] ));
			}
		    }
		} 
            
	     
	      
	      for (int i=0;i<MemeEvo.size();i++)
		{
		  pair<MemeNum::iterator, MemeNum::iterator> itp=tempmeme.equal_range( MemeEvo[i] ); 
		  int ponum=0;
		  int abunum=0;
		  for (Mapiter=itp.first; Mapiter!=itp.second; Mapiter++  )
		    {
		      ponum=ponum+1;
		      abunum=abunum+(*Mapiter).second;
		    }
		  Abundancefile32<<ponum<<endl;
		  Abundancefile311<<setw(10)<<abunum<<endl;
		  if( ponum > N )
		    {
		      cout<<"ponum is large !!"<<endl;
		      break;
		    }
		}
	      
	    }//for the if 2.abundance 
	  
	  
	  
	}// one runtime
     
    }//for Repit time of network
  
  double finish=clock();
  
  test<<"N "<<setw(10)<<N<<" and  K"<<setw(10)<<K<<"is the networksize"<<endl;  
  test<<"MemoryNum is  "<<setw(10)<< Capacity <<setw(10)<<"  and PN  "<<setw(10)<<PN<<endl;
  test<<"runtime is   "<<runtime<<endl;
  test<< "Running time is: "<<(double)(finish-start)/CLOCKS_PER_SEC/3600<<"   hours"<<endl; 
  
    
    
  ER.close();
  MemeNumfile.close();
  LifeTimefile.close(); 
  Abundancefile32.close();
  Abundancefile311.close();
  degree.close();
  
    
  return 0;
}

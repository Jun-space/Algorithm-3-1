#include <iostream>
#include <vector>
using namespace std;
void flip(vector<int>& fish,int l,int r){
	for(int i=0;i<(r-l)/2+1;i++){
		int tmp=fish[l+i];
		fish[l+i]=-fish[r-i];
		fish[r-i]=-tmp;
	}
}
bool verify(vector<int> fish,int n){
	for(int i=1;i<=n;i++){
		if(fish[i]!=i)
			return false;
	}
	return true;
}
bool checkTwo(vector<int> fish,int n,int l,int r){
	int lIndex=0;
	int rIndex=0;
	for(int i=1;i<r-l;i++){
		if(fish[l+i]> 0){
			lIndex=l+i;
			break;
		}
	}
	for(int i=1;i<r-l;i++){
		if(fish[r-i]>0){
			rIndex=r-i;
			break;
		}
	}
	if(lIndex==0){
		int h;
		for(int i=0;i<r-l;i++){
			if (fish[l+i]+1!=fish[l+i+1]){
				h=l+i;
				break;
			}
		}
		vector<int> v(fish.begin(),fish.end());
		flip(v,l,h);
		flip(v,h+1,r);
		if(verify(v,n))return true;
		return false;
	}
	if(fish[lIndex]==lIndex){
		vector<int> v(fish.begin(),fish.end());
		flip(v,l,lIndex-1);
		flip(v,rIndex+1,r);
		if(verify(v,n))return true;
	}
	vector<int> v(fish.begin(),fish.end());
	flip(v,lIndex,rIndex);
	flip(v,l,r);
	if(verify(v,n))return true;
	return false;
}
bool checkTwoLeft(vector<int> fish,int n,int l,int r){
	int index=0;
	int size=1;
	for(int i=1;i<=r-l;i++){
		if(fish[r-i]<0){
			index=r-i;
			while(index>l&&fish[index]-1==fish[index-1]){
				size++;
				index--;
			}
			break;
		}
	}
	vector<int> v(fish.begin(),fish.end());
	flip(v,index,r);
	flip(v,l,r-size);
	if(verify(v,n))return true;
	return false;
}
bool checkTwoRight(vector<int> fish,int n,int l,int r){
	int index=0;
	int size=1;
	for(int i=1; i<=r-l;i++){
		if(fish[l+i]<0){
			index=l+i;
			while(index<r&&fish[index]+1==fish[index+1]){
				size++;
				index++;
			}
			break;
		}
	}
	vector<int> v(fish.begin(),fish.end());
	flip(v,l,index);
	flip(v,l+size,r);
	if(verify(v,n))return true;
	return false;
}
int solution(vector<int> fish,int n){
	int l=0;
	int r=0;
	bool lSign=true;
	bool rSign=true;

	for(int i=1;i<=n;i++){
		if(fish[i]!=i){
			l=i;
			if(fish[i]<0)lSign=false;
			break;
		}
	}
	for(int i=n;i>=1;i--){
		if(fish[i]!=i){
			r=i;
			if(fish[i]<0)rSign=false;
			break;
		}
	}
	if(!lSign&&!rSign){
		vector<int> v(fish.begin(),fish.end());
		flip(v,l,r);
		if(verify(v,n))return 1;
		if(checkTwo(fish,n,l,r))return 2;
	}
	if (!lSign&&rSign)
		if(checkTwoLeft(fish,n,l,r))return 2;
	if(lSign&&!rSign)
		if(checkTwoRight(fish,n,l,r))return 2;
	return 3;
}
int main(){
	int n;
	vector<int> fish[5];
	cin>>n;
	for(int i=0;i<5;i++){
		fish[i].push_back(0);
		for(int j=1;j<=n;j++){
			int t;
			cin>>t;
			fish[i].push_back(t);
		}
	}
	for(int i=0;i<5;i++){
		int result=solution(fish[i],n);
		if(result==1)cout<<"one\n";
		if(result==2)cout<<"two\n";
		if(result==3)cout<<"over\n";
	}
	return 0;
}
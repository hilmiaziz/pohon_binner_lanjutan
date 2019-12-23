#include <iostream>
#include <conio.h>
#include <sstream>
#include <algorithm>
#include <cstdio>

#define pow2(n)(1<<(n))
using namespace std;

struct simpulavl{
	int data;
	struct simpulavl *kiri;
	struct simpulavl *kanan;
}*akar;

class pohonavl{
	public:
	int tinggi(simpulavl *);
	int selisih(simpulavl *);
	simpulavl *rotasi_rr(simpulavl *);
	simpulavl *rotasi_ii(simpulavl *);
	simpulavl *rotasi_ir(simpulavl *);
	simpulavl *rotasi_ri(simpulavl *);
	simpulavl *setimbang(simpulavl *);
	simpulavl *sisip(simpulavl *,int);
	void tampil (simpulavl *,int);
	void inorder (simpulavl *);
	void preorder (simpulavl *);
	void postorder (simpulavl *);
	
	pohonavl(){
		akar = NULL;
	}
};

int main(){
	int pilihan,item;
	pohonavl AVL;
	while(1){
		cout<<"\n......................."<<endl;
		cout<<"\nImplementasi Pohon AVL "<<endl;
		cout<<"\n......................."<<endl;
		cout<<"\n1. Sisipkan elemen ke dalam pohon "<<endl;
		cout<<"\n2. Tampilkan Pohon AVL Seimbang "<<endl;
		cout<<"\n3. Penjelajahan InOrder "<<endl;
		cout<<"\n4. Penjelajahan PreOrder "<<endl;
		cout<<"\n5. Penjelajahan Postorder "<<endl;
		cout<<"\n6. Keluar "<<endl;
		cout<<"\nMasukan Pilihan Anda : ";
		
		cin>>pilihan;
		switch(pilihan){
			case 1:
				cout<<"Masukan nilai yang akan disisipkan : ";
				cin>>item;
				akar = AVL.sisip(akar,item);
				break;
				
			case 2:
				if(akar == NULL){
					cout<<"Pohon Kosong"<<endl;
					continue;
				}
				cout<<"Pohon AVL Seimbang: "<<endl;
				AVL.tampil(akar,1);
				break;
				
			case 3:
				cout<<"Jelajah Inorder : ";
				AVL.inorder(akar);
				cout<<endl;
				break;
				
			case 4:
				cout<<"Jelajah PreOrder : ";
				AVL.preorder(akar);
				cout<<endl;
				break;
				
			case 5:
				cout<<"Jelajah PostOrder : ";
				AVL.postorder(akar);
				cout<<endl;
				break;
				
			case 6:
				exit(1);
				break;
			default :
				cout<<"pilihan salah"<<endl;
		}
	}
	getch();
	return 0;
}
int pohonavl::tinggi(simpulavl*temp){
	int h=0;
	if(temp !=NULL){
		int tinggiL = tinggi(temp->kiri);
		int tinggiR = tinggi(temp->kanan);
		int tinggiMaks = max(tinggiL,tinggiR);
		h = tinggiMaks +1;
	}
	return h;
}
int pohonavl::selisih(simpulavl*temp){
		int tinggiL = tinggi(temp->kiri);
		int tinggiR = tinggi(temp->kanan);
		int faktorB = tinggiL - tinggiR;
		return faktorB;
}
simpulavl*pohonavl::rotasi_rr(simpulavl*induk){
	simpulavl*temp;
	temp=induk->kanan;
	induk->kanan = temp->kiri;
	temp->kiri = induk;
	return temp;
}
simpulavl*pohonavl::rotasi_ii(simpulavl*induk){
	simpulavl*temp;
	temp=induk->kiri;
	induk->kiri = temp->kanan;
	temp->kanan = induk;
	return temp;
}
simpulavl*pohonavl::rotasi_ir(simpulavl*induk){
	simpulavl*temp;
	temp=induk->kiri;
	induk->kiri = rotasi_ir(temp);
	return rotasi_ii (induk);
}
simpulavl*pohonavl::rotasi_ri(simpulavl*induk){
	simpulavl*temp;
	temp=induk->kanan;
	induk->kanan = rotasi_ii(temp);
	return rotasi_rr (induk);
}
simpulavl*pohonavl::setimbang(simpulavl*temp){
	int faktor_seimbang = selisih(temp);
	if(faktor_seimbang>1){
		if(selisih(temp->kiri)>0)
		temp = rotasi_ii (temp);
		else
		temp = rotasi_ir(temp);
	}
	else if(faktor_seimbang<-1){
		if(selisih(temp->kanan)>0)
		temp = rotasi_ri(temp);
		else
		temp = rotasi_rr (temp);
	}
	return temp;
}
simpulavl*pohonavl::sisip(simpulavl*akar,int nilai){
	if(akar==NULL){
		akar = new simpulavl;
		akar->data = nilai;
		akar->kiri=NULL;
		akar->kanan = NULL;
		return akar;
	}
	else if(nilai<akar->data){
		akar->kiri=sisip(akar->kiri,nilai);
		akar=setimbang(akar);
	}
	return akar;
}
void pohonavl::tampil(simpulavl*ptr,int level){
	int i;
	if(ptr!=NULL){
		tampil(ptr->kanan,level+1);
		cout<<"\n";
		if(ptr==akar)
		cout<<"akar->";
		for(i=0;i<level&&ptr!=akar;i++)
		cout<<"  ";
		cout<<ptr->data;
		tampil(ptr->kiri,level+1);
	}
}
void pohonavl::inorder(simpulavl*pohon){
	if(pohon == NULL)
	return;
	inorder(pohon->kiri);
	cout<<pohon->data<<" ";
	inorder(pohon->kanan);
}
void pohonavl::preorder(simpulavl*pohon){
	if(pohon == NULL)
	return;
	cout<<pohon->data<<" ";
	preorder(pohon->kiri);
	preorder(pohon->kanan);
}
void pohonavl::postorder(simpulavl*pohon){
	if(pohon == NULL)
	return;
	postorder(pohon->kiri);
	postorder(pohon->kanan);
	cout<<pohon->data<<" ";
}


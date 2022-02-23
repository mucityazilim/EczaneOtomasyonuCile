#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ECZANE OTOMASYONU 
// Mucit Yazýlým- Sadýk ÞAHÝN

typedef struct hasta {
	char tc[12];           //birincil anahtar 
	char adSoyad[20]; 
	char cinsiyet; 
	char adres[20]; 
	char tel[20]; 
	int guvence; 	
	
} hasta ;

typedef struct ilac {
	int barkod;          // birincil anahtarý 
	char ilacAdi[20]; 
	char ureticiFirma[20]; 
	int adet; 
	float fiyat; 	
} ilac  ; 

typedef struct satis {
	char hastaTC[12]  ;    // yabancýl anahtar 
	int ilacBarkod;        // yabancýl anahtar 
	int adet; 
	char tarih[10]; 
	float fiyat; 
} satis ;



void stokGuncelle( int barkod, int adet  )
{
		
	ilac i1; 
	int sonuc=0, sayac=0; 
	
	
	FILE *ptr= fopen("ilaclar.dat", "r+b") ; 
	
	while(  fread(&i1, sizeof(ilac), 1, ptr) !=NULL  )
	{
		if( barkod == i1.barkod )
		{
			sonuc=1; 
			break; 			
		} 
		sayac++; 		
	}
	
	if( sonuc==0  )
	{		 
		fclose(ptr); 		
	}
	else
	{
	 
		rewind(ptr); 
		
		
		i1.adet= i1.adet - adet  ; 
		
		fseek (ptr, (sayac )  * sizeof(ilac),  0 ); 		
		fwrite (&i1, sizeof(ilac)  , 1, ptr) ; 
		fclose(ptr) ; 
		printf("Stok kismindan ilac eksildi \n"); 
	}		
	
}


void satisYap()
{
	system("cls"); 
	printf("Satis ekrani \n") ; 
	satis s1; 
	hasta h1; 
	ilac i1; 
	int hsonuc=0, isonuc=0; 
	
		
	printf("Hasta TC     : ") ; scanf(" %[^\n]s", s1.hastaTC ); 
	printf("Ilac Barkod  : ") ; scanf("%d", &s1.ilacBarkod ); 
	printf("Adet (Kutu)  : ") ; scanf("%d", &s1.adet ); 
	
	FILE *hptr= fopen("hastalar.dat", "r+b") ; 
	FILE *iptr= fopen("ilaclar.dat", "r+b") ; 
	
	while(  fread(&h1, sizeof(hasta), 1, hptr) !=NULL  )
	{
		if( strcmp( s1.hastaTC, h1.tc  ) ==0  )
		{
			hsonuc=1; 
			break; 
		}				
	}
	
	while(  fread(&i1, sizeof(ilac), 1, iptr) !=NULL  )
	{
		if( s1.ilacBarkod == i1.barkod    )
		{
			isonuc=1; 
			break; 
		}				
	}
	fclose(iptr); 
	fclose(hptr); 
	
	if( hsonuc==0)
	{
		printf("Hatali TC numarasi !\n") ; 
		return ; 
	}
	if( isonuc==0)
	{
		printf("Hatali barkod numarasi !\n") ; 
		return ; 
	}
	if(  s1.adet > i1.adet )
	{
		printf("Stokta yeterli miktarda ilac yok !\n") ; 
		return ; 
	}
	else
	{
		FILE * sptr= fopen("satislar.txt", "a" ); 
		float toplamFiyat; 
		toplamFiyat= s1.adet * i1.fiyat; 
		time_t satisTarihi= time(NULL); 
		
		fprintf( sptr, "************************ \n"    ) ; 
		
		fprintf( sptr, "Satis Tarihi   : %s \n", ctime(&satisTarihi)     ) ; 
		fprintf( sptr, "Kisi Bilgileri : %s\t%s\t%s\n", h1.tc, h1.adSoyad, h1.tel    ) ; 
		fprintf( sptr, "Ilac Bilgileri : %d\t%s\n", i1.barkod, i1.ilacAdi     ) ; 
		fprintf( sptr, "Ucret Bilgileri [adet/fiyat/toplamucret] : %d\t%f\t%f\n", s1.adet, i1.fiyat, toplamFiyat      ) ; 
		fclose(sptr); 
		printf("Satis tamam \n")		; 
		printf("Toplam ucret: %.2f TL \n", toplamFiyat ); 
		
		stokGuncelle( s1.ilacBarkod, s1.adet); 		
	}	
}

int guvence () 
{
	int secim; 
	printf("GUVENCE : \n") ; 
	printf("1- SGK \n"); 
	printf("2- GSK \n"); 
	printf("3- EMEKLI SANDIGI \n"); 
	printf("4- Guvenci kaydi yok \n"); 
	printf("seciminiz : ");  scanf("%d", &secim); 
	return secim; 
	
}

void hastaKaydi()
{
	system("cls") ; 
	
	hasta h1; 
	
	printf("Hasta kayit ekrani \n"); 
	printf("TC       : "); scanf(" %[^\n]s", h1.tc ) ; 
	printf("Ad-Soyad : "); scanf(" %[^\n]s", h1.adSoyad ) ; 
	printf("Cinsiyet : "); scanf(" %c", &h1.cinsiyet ) ; 
	printf("Adres    : "); scanf(" %[^\n]s", h1.adres ) ; 
	printf("Telefon  : "); scanf(" %[^\n]s", h1.tel ) ; 	
	h1.guvence= guvence(); 
	
	FILE *ptr= fopen("hastalar.dat", "a+b") ; 
	fwrite(&h1, sizeof(hasta), 1, ptr); 
	fclose(ptr); 
	printf("Hasta kaydi tamam \n"); 
	
	
	
			
}
void ilacKaydi() 
{
	system("cls") ; 
	
	ilac i1; 
	
	printf("Ilac kayit ekrani \n"); 
	printf("Barkod No     : "); scanf(" %d", &i1.barkod ) ; 
	printf("Ilac Adi      : "); scanf(" %[^\n]s", i1.ilacAdi ) ; 
	printf("Uretici Firma : "); scanf(" %[^\n]s", i1.ureticiFirma ) ; 
	printf("Adet (Kutu)   : "); scanf(" %d", &i1.adet ) ; 
	printf("Fiyat         : "); scanf(" %f", &i1.fiyat ) ; 	
	
	FILE *ptr= fopen("ilaclar.dat", "a+b") ; 
	fwrite(&i1, sizeof(ilac), 1, ptr); 
	fclose(ptr); 
	printf("Ilac kaydi tamam \n"); 	
}

void hastalariListele() 
{
	system("cls") ; 
	
	hasta h1; 
	
	printf("Hasta listele ekrani \n"); 
	printf("%-12s%-20s%-10s%-20s%-11s%-8s\n", "TC","AD-SOYAD","CINSIYET","ADRES", "TELEFON", "GUVENCE"   ) ; 
	
	FILE *ptr= fopen("hastalar.dat", "r+b") ; 
	
	while(  fread(&h1, sizeof(hasta), 1, ptr) !=NULL  )
	{
		printf("%-12s%-20s%-10c%-20s%-11s%-8d\n",  h1.tc, h1.adSoyad, h1.cinsiyet, h1.adres, h1.tel, h1.guvence   ) ; 
		
				
	}
	
	fclose(ptr); 	
}
void ilaclariListele() 
{
	system("cls") ; 
	
	ilac i1; 
	
	printf("Ilac listeleme ekrani \n\n"); 
	printf("%-12s%-20s%-20s%-12s%-10s\n", "BARKOD NO","ILAC ADI","FIRMA ADI","ADET(KUTU)", "FIYAT (TL)" ) ; 
	
	FILE *ptr= fopen("ilaclar.dat", "r+b") ; 
	
	while(  fread(&i1, sizeof(ilac), 1, ptr) !=NULL  )
	{
		printf("%-12d%-20s%-20s%-12d%.2f TL\n",   i1.barkod, i1.ilacAdi, i1.ureticiFirma, i1.adet, i1.fiyat    ) ; 				
	}
	
	fclose(ptr); 		
}

void ilacGuncelle() 
{
	system("cls") ; 
	
	ilac i1; 
	int barkod, yeniAdet; 
	float  yeniFiyat; 
	int sonuc=0, sayac=0; 
	
	printf("Ilac Guncelleme ekrani \n\n"); 
	printf("Guncellemek istediginiz ilacin barkod No : ") ; scanf("%d", &barkod); 	
	
	FILE *ptr= fopen("ilaclar.dat", "r+b") ; 
	
	while(  fread(&i1, sizeof(ilac), 1, ptr) !=NULL  )
	{
		if( barkod == i1.barkod )
		{
			sonuc=1; 
			printf("%-12d%-20s%-20s%-12d%.2f TL\n\n",   i1.barkod, i1.ilacAdi, i1.ureticiFirma, i1.adet, i1.fiyat    ) ; 			
			break; 			
		} 
		sayac++; 		
	}
	
	if( sonuc==0  )
	{
		printf("%d barkod numarali ilac kaydi yok ! \n", barkod); 		
		fclose(ptr); 		
	}
	else
	{
		printf("Yeni stok adeti : "); scanf("%d", &yeniAdet); 
		printf("Yeni fiyat TL   : "); scanf("%f", &yeniFiyat); 
		
		rewind(ptr); 
		
		
		i1.adet= yeniAdet; 
		i1.fiyat= yeniFiyat; 
		
		fseek (ptr, (sayac )  * sizeof(ilac),  0 ); 		
		fwrite (&i1, sizeof(ilac)  , 1, ptr) ; 
		fclose(ptr) ; 
		printf("Ilac guncelleme islemi tamam \n"); 
	}		
}
void satislariRaporla() 
{
	system("cls"); 
	printf("Satis rapor ekrani\n\n") ; 
	FILE *ptr= fopen("satislar.txt", "r"); 
	char ch; 
	if( ptr!=NULL )
	while( !feof(ptr) )
	{
		ch= fgetc(ptr); 
		printf("%c", ch); 
	}
	else
	printf("Her hangi bir satis yapilmamis \n"); 	
	fclose(ptr); 
	
}


void ilacKaydiSil() 
{
	system("cls") ; 	
	printf("Ilac kaydi silme ekrani \n\n"); 
	int barkod; 
	ilac i1; 
	int sonuc=0; 
	printf("Barkod no : "); scanf("%d", &barkod); 
	FILE *ptr= fopen("ilaclar.dat", "r+b"); 
	FILE *yptr= fopen("yedek.dat", "w+b"); 
	
	while( fread(&i1, sizeof(ilac), 1, ptr) !=NULL )
	{
		if( barkod != i1.barkod )
		fwrite(&i1, sizeof(ilac), 1, yptr) ; 	
		else
		{
			sonuc =1; 			
		}	
	}
	
	fclose(ptr); 
	fclose(yptr); 
	
	if( sonuc == 1 )
	{
	remove("ilaclar.dat"); 
	rename("yedek.dat","ilaclar.dat" ); 
	printf("%d barkod numarali ilac kaydi silindi \n", barkod); 
	}
	else
	printf("%d barkod numarali ilac kaydiniz bulunamadi !\n" , barkod ) ; 	
}

void kisiKaydiSil()
{
	system("cls") ; 	
	printf("Kisi kaydi silme ekrani \n\n"); 
	char tc[20]; 
	hasta  h1; 
	int sonuc=0; 
	printf("Kisi TC : "); scanf(" %[^\n]s", tc ); 
	FILE *ptr= fopen("hastalar.dat", "r+b"); 
	FILE *yptr= fopen("yedek.dat", "w+b"); 
	
	while( fread(&h1, sizeof(hasta ), 1, ptr) !=NULL )
	{
		if( strcmp( tc, h1.tc)==0 )
		sonuc=1; 
		else		
		fwrite(&h1, sizeof(hasta) , 1, yptr) ; 	
	}
	
	fclose(ptr); 
	fclose(yptr); 
	
	if( sonuc == 1 )
	{
	remove("hastalar.dat"); 
	rename("yedek.dat","hastalar.dat" ); 
	printf("%s TC numarali kisi kaydi silindi \n", tc); 
	}
	else
	printf("%s TC numarali kisi kaydi bulunamadi !\n" , tc ) ; 	
}

int menu() 
{
	int secim; 
	
	printf("\nECZANE OTOMASYONU \n") ;
	printf("1- Satis yap \n") ;
	printf("2- Hasta kaydi\n") ;
	printf("3- Hastalari listele\n") ;
	printf("4- Ilac kaydi  \n") ;
	printf("5- Ilaclari listele \n") ;
	printf("6- Ilac guncelle \n") ;
	printf("7- Satislari raporla \n") ;
	printf("8- Ilac kaydi sil \n") ;
	printf("9- Kisi kaydi sil \n") ;	
	printf("0- Programi kapat  \n") ;
	printf("Seciminiz : ") ; scanf("%d", &secim); 
	return secim; 
	
}




int main() 
{
	int secim= menu(); 
	while( secim != 0 )
	{
		switch(secim )
		{
			case 1: satisYap(); break; 
			case 2: hastaKaydi(); break; 
			case 3: hastalariListele(); break; 
			case 4: ilacKaydi(); break; 			
			case 5: ilaclariListele(); break; 
			case 6: ilacGuncelle(); break; 
			case 7: satislariRaporla(); break; 
			case 8: ilacKaydiSil(); break; 
			case 9: kisiKaydiSil(); break; 
			case 0: break; 
			default: printf("hatali secim yaptiniz !\n") ;break; 
		}
		secim= menu(); 
	}
	
	
	return 0; 
}





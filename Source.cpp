#include<iostream>
#include<ctime> // Kirjasto time funktiolle
#include<cstdlib> // Kirjasto srand ja rand funktiolle
#include<string> // Kirjasto getline funktiolle
using namespace std;

void varausnumeroGeneraattori(int varausnumerot[], int asiakasMaara); // Alustetaan varausnumeroiden arvonta funktio

// Funktio huoneiden maaran arpomiselle
int arvoHuoneidenMaara() {
	int huoneidenMaara;	// Alustetaan muuttuja huoneiden maaralle
	bool parillinen = false; // Alustetaan bool muuttuja jolla pyoritetaan do while looppia
	do {
		srand(time(0)); // Alustetaan srand ja time funktio etta voin kayttaa rand funktiota
		for (int i = 0; i < 1; i++) {
			huoneidenMaara = rand() % 260 + 40; // Arvotaan huoneiden maara valilta 40 - 300
		}
		if (huoneidenMaara % 2 == 0) { // Tarkistetaan onko luku parillinen vai pariton
			parillinen = true;		   // Jos luku parillinen lopeta looppi jos pariton jatka looppia
		}
	} while (parillinen == false);
	return huoneidenMaara; // Palautetaan arvottu parillinen huoneiden maara
}

// Funktio vapaiden huoneiden laskemiseen
int jaljellaOlevienHuoneidenMaara(bool huoneet[], int huoneidenMaara) {
	int huoneLaskin = 0; // Alustetaan huoneiden maaran laskuri
	for (int i = 0; i < huoneidenMaara; i++) { // Pyoritetaan for looppia niin monta kertaa kuin huoneita on kokonaisuudessaan
		if (huoneet[i] == false) {			   // Jos huoneet taulun kentta on false eli huone on vapaa
			huoneLaskin++;					   // Nostetaan huoneLaskin muuttujan arvoa yhdella
		}
	}
	return huoneLaskin;
}

// Funktio alennuksen arpomiselle
double arvoAlennus() {
	int arvottuLuku;
	double alennusMaara = 0.0;
	srand(time(0)); // Alustetaan srand ja time funktio etta voin kayttaa rand funktiota
	arvottuLuku = rand() % 3 + 1; // Arvotaan luku valilta 1 - 3
	
	// Jos int arvottuLuku on 1 alennus on 0%, 2 alennus on 10% tai 3 alennus on 20%
	if (arvottuLuku == 1) {
		alennusMaara = 0.0;
	}
	else if (arvottuLuku == 2) {
		alennusMaara = 10.0;
	}
	else if (arvottuLuku == 3) {
		alennusMaara = 20.0;
	}
	return alennusMaara; // Palautetaan arvottu alennus
}

// Alustetaan asiakkaan tietoja varten struct
struct Varaaja {
	string nimi;
	int yomaara;
	int varausnumero;
	int huoneTyyppi;
	int huoneNumero;
	double hinta;
	double alennusPros;
	double lopullinenHinta;
};

// Funktio asiakkaan tietojen keraamiseen
Varaaja luoAsiakas(bool huoneet[], int huoneidenMaara, int asiakasLaskin) {
	Varaaja asiakasTemp; // Alustetaan struct
	int viimeinenPieniHuone = huoneidenMaara / 2;
	int viimeinenIsoHuone = huoneidenMaara - 1;
	bool tarkistus = false;
	cout << "Anna nimesi: ";
	cin.ignore();
	getline(cin, asiakasTemp.nimi);

	do { // Aloitetaan do while huone tyypin kysymista varten
		cout << "Haluatko asua yhden vai kahden hengen huoneessa: ";
		if (!(cin >> asiakasTemp.huoneTyyppi)) { // Kysytaan kayttajalta haluaako han asua 1 vai 2 hengen huoneessa
			cin.clear();						 // Jos kayttaja syottaa jotain muuta kuin 1 tai 2, cin saa arvon false ja taman jalkeen
			cin.ignore(10000, '\n');			 // cin.clear() ja cin.ignore() tyhjentavat kentan ja siirtyvat eteenpain
			tarkistus = false;					 // Asetetaan myos tarkistus falseksi jotta do while jatkuu
		}
		if (asiakasTemp.huoneTyyppi && asiakasTemp.huoneTyyppi == 1 || asiakasTemp.huoneTyyppi == 2) { // Jos cin arvo on true
			tarkistus = true;						// ja cin arvo on 1 tai 2, tarkistus asetetaan trueksi ja do while loppuu
		}
	} while (!tarkistus);

	do { // Aloitetaan do while oiden maaran kysymista varten
		cout << "Montako yota haluat olla hotellissa: ";
		if (!(cin >> asiakasTemp.yomaara)) { // Jos cin on saanut vaaran arvon eli jonkun muun kuin integerin cin saa arvon false
			cin.clear();					 // cin.clear() ja cin.ignore() tyhjentavat kentan ja siirtyvat eteenpain
			cin.ignore(10000, '\n');
		}
	} while (!asiakasTemp.yomaara); // Jos cin on saanut hyvaksyttavan arvon eli intger arvon do while loppuu

	if (asiakasTemp.huoneTyyppi == 1) { // Jos kayttaja on valinnut yhden hengen huoneen
		for (int i = 0; i < viimeinenPieniHuone; i++) { // Pyoritetaamn for looppia huoneidenMaara / 2 kertaa
			if (huoneet[i] == false) {					// Jos tarkasteltava huone on false eli vapaa
				asiakasTemp.huoneNumero = i;			// Ohjelma ottaa huoneet taulun vapaan kentan numeron ylos ja kirjaa sen structiin
				break;
			}
		}
	} else if (asiakasTemp.huoneTyyppi == 2) { // Jos kayttaja on valinnut kahden hengen huoneen
		for (viimeinenPieniHuone; viimeinenPieniHuone < viimeinenIsoHuone; viimeinenPieniHuone++) { // Aloitetaan for looppi ylemman for loopin viimeisesta luvusta
			if (huoneet[viimeinenPieniHuone] == false) {											// Jos tarkasteltava huone on false eli vapaa
				asiakasTemp.huoneNumero = viimeinenPieniHuone;										// Ohjelma ottaa huoneet taulun vapaan kentan ylos ja kirjaa sen structiin
				break;
			}
		}
	}
	if (asiakasTemp.huoneTyyppi == 1) { // Jos kayttaja on valinnut yhden hengen huoneen lasketaan tilauksen hinta
		asiakasTemp.hinta = 100.0 * asiakasTemp.yomaara; // Lasketaan hinta 100 * oiden maaralla ja tallennetaan se structin hinta kenttaan
	}
	else if (asiakasTemp.huoneTyyppi == 2) { // Jos kayttaja on valinnut kahden hengen huoneen lasketaan tilauksen hinta
		asiakasTemp.hinta = 150.0 * asiakasTemp.yomaara;
	}

	return asiakasTemp; // Palautetaan struct arvoineen paaohjelmalle
}

Varaaja muokkaaAsiakas(string nimi, int huoneTyyppi, int huoneNumero, int yomaara, int huoneidenMaara, bool huoneet[], int alennusPros) {
	Varaaja asiakasTemp; // Alustetaan struct
	int toiminto = 0;
	bool tarkistus = false;
	int viimeinenPieniHuone = huoneidenMaara / 2;
	int viimeinenIsoHuone = huoneidenMaara - 1;
	asiakasTemp.nimi = nimi;
	asiakasTemp.huoneTyyppi = huoneTyyppi;
	asiakasTemp.huoneNumero = huoneNumero;
	asiakasTemp.yomaara = yomaara;
	asiakasTemp.alennusPros = alennusPros;
	huoneet[huoneNumero] = false;
	cout << "Asiakkaan nimi:\t\t" << nimi << endl;
	cout << "Oiden maara:\t\t" << yomaara << endl;
	cout << "Huoneen tyyppi:\t\t" << huoneTyyppi << endl;
	do {
		cout << "Mita haluat tehda 1 = Muokkaa nimea, 2 = Muokkaa oiden maaraa, 3 = Muokkaa huoneen tyyppia, 4 = Lopeta muokkaaminen";
		cin >> toiminto;
		switch (toiminto) {
		case 1:
			cout << "Anna uusi nimi: ";
			cin.ignore();
			getline(cin, asiakasTemp.nimi);
		break;
		case 2:
			cout << "Anna uusi oiden maara: ";
			cin >> asiakasTemp.yomaara;
			break;
		case 3:
			do { // Aloitetaan do while huone tyypin kysymista varten
				cout << "Anna uusi huoneen tyyppi 1 = yhden hengen huone, 2 = kahden hengen huone: ";
				if (!(cin >> asiakasTemp.huoneTyyppi)) { // Kysytaan kayttajalta haluaako han asua 1 vai 2 hengen huoneessa
					cin.clear();						 // Jos kayttaja syottaa jotain muuta kuin 1 tai 2, cin saa arvon false ja taman jalkeen
					cin.ignore(10000, '\n');			 // cin.clear() ja cin.ignore() tyhjentavat kentan ja siirtyvat eteenpain
					tarkistus = false;					 // Asetetaan myos tarkistus falseksi jotta do while jatkuu
				}
				if (asiakasTemp.huoneTyyppi && asiakasTemp.huoneTyyppi == 1 || asiakasTemp.huoneTyyppi == 2) { // Jos cin arvo on true
					tarkistus = true;						// ja cin arvo on 1 tai 2, tarkistus asetetaan trueksi ja do while loppuu
				}
			} while (!tarkistus);
			if (asiakasTemp.huoneTyyppi == 1) { // Jos kayttaja on valinnut yhden hengen huoneen
				for (int i = 0; i < viimeinenPieniHuone; i++) { // Pyoritetaamn for looppia huoneidenMaara / 2 kertaa
					if (huoneet[i] == false) {					// Jos tarkasteltava huone on false eli vapaa
						asiakasTemp.huoneNumero = i;			// Ohjelma ottaa huoneet taulun vapaan kentan numeron ylos ja kirjaa sen structiin
						break;
					}
				}
			}
			else if (asiakasTemp.huoneTyyppi == 2) { // Jos kayttaja on valinnut kahden hengen huoneen
				for (viimeinenPieniHuone; viimeinenPieniHuone < viimeinenIsoHuone; viimeinenPieniHuone++) { // Aloitetaan for looppi ylemman for loopin viimeisesta luvusta
					if (huoneet[viimeinenPieniHuone] == false) {											// Jos tarkasteltava huone on false eli vapaa
						asiakasTemp.huoneNumero = viimeinenPieniHuone;										// Ohjelma ottaa huoneet taulun vapaan kentan ylos ja kirjaa sen structiin
						break;
					}
				}
			}
			break;
		}
		if (asiakasTemp.huoneTyyppi == 1) { // Jos kayttaja on valinnut yhden hengen huoneen lasketaan tilauksen hinta
			asiakasTemp.hinta = 100.0 * asiakasTemp.yomaara; // Lasketaan hinta 100 * oiden maaralla ja tallennetaan se structin hinta kenttaan
		}
		else if (asiakasTemp.huoneTyyppi == 2) { // Jos kayttaja on valinnut kahden hengen huoneen lasketaan tilauksen hinta
			asiakasTemp.hinta = 150.0 * asiakasTemp.yomaara;
		}
	} while (toiminto != 4);
	
	return asiakasTemp; // Palautetaan muokattu struct arvoineen paaohjelmalle
}

int main() {
	int teapot = 10;
	const int asiakasMaara = 300; // Alustetaan vakio joka kertoo asiakkaiden maksimi maaran
	int toiminto = 0, asiakasLaskin = 1;
	string nimi;
	Varaaja asiakas[asiakasMaara]; // Alustetaan struct ja annetaan structille maksimi arvo 300
	int huoneidenMaara = 0, vapaidenHuoneidenMaara = 0; // Alustetaan muuttujat huoneiden maaralle
	int varausnumeroTaulu[asiakasMaara]; // Alustetaan taulu arvotuille varausnumeroille ja rajataan kenttien maara max 300
	huoneidenMaara = arvoHuoneidenMaara(); // Laitetaan arvottu huoneiden maara muuttujaan
	varausnumeroGeneraattori(varausnumeroTaulu, asiakasMaara);
	bool* huoneet = new bool[huoneidenMaara]; // Luodaan bool tyyppinen taulu viittausparametrilla ja annetaan huoneet taululle arvoksi 
											  // uusi bool tyyppinen taulu jonka koko maaraytyy arvotun luvun mukaan

	for (int i = 0; i < huoneidenMaara; i++) { // Alustetaan koko huoneet taulu muuttamalla jokainen taulun kentta falseksi
		huoneet[i] = false;					   // false = huone on vapaa, true = huone varattu
	}
	
	do { // do while looppi koko ohjelman pyorittamiseen, looppi on paalla niin kauan kun kayttaja lopettaa sen
		vapaidenHuoneidenMaara = jaljellaOlevienHuoneidenMaara(huoneet, huoneidenMaara); // Haetaan vapaiden huoneiden maara funktiolla jaljellaOlevienHuoneidenMaara()
		int pienetHuoneetYhteensa = huoneidenMaara / 2; // Lasketaan kuinka monta yhden hengen huonetta on yhteensa
		int isotHuoneetYhteensa = huoneidenMaara / 2;   // Lasketaan kuinka monta kahden hengen huonetta on yhteensa
		int yhh = 0; // Alustetaan muuttuja yhden hengen huoneiden maaralle
 		int khh = 0; // Alustetaan muuttuja kahden hengen huoneiden maaralle
		int t = 0;
		for (int i = 0; i < asiakasLaskin; i++) { // Kaydaan lapi kaikki asiakkaat
			if (asiakas[i].huoneTyyppi == 1) { // Jos asiakas on varannut yhden hengen huoneen lisataan int yhh arvoa yhdella
				yhh++;
			}
			else if (asiakas[i].huoneTyyppi == 2) { // Jos asiakas on varannut kahden hengen huoneen lisataan int khh arvoa yhdella
				khh++;
			}
		}
		int vapaatPienetHuoneet = pienetHuoneetYhteensa - yhh; // Vahennetaan varattujen yhden hengen huoneiden maara kaikista yhden hengen huoneista
		int vapaatIsotHuoneet = isotHuoneetYhteensa - khh; // Vahennetaan varattujen kahden hengen huoneiden maara kaikista kahden hengen huoneista
		if (vapaidenHuoneidenMaara > 0) {
			cout << "Tervetuloa Eeron hotelliin!" << endl;
			cout << "Huoneita yhteensa " << huoneidenMaara << endl;
			cout << "Vapaita huoneita tarjolla yhteensa " << vapaidenHuoneidenMaara << endl;
			cout << "Vapaita yhden hengen huoneita tarjolla " << vapaatPienetHuoneet << endl;
			cout << "Vapaita kahden hengen huoneita tarjolla " << vapaatIsotHuoneet << endl;
			cout << "Mita haluat tehda?" << endl;
			cout << "1 = Varaa huone, 2 = Nayta asiakkaiden tiedot, 3 = Tulosta huoneet, 4 = Muokkaa asiakkaan tietoja, 5 = Lopeta" << endl;
			do {
				if (!(cin >> toiminto)) { // Jos cin on saanut vaaran arvon eli jonkun muun kuin integerin cin saa arvon false
					cin.clear();					 // cin.clear() ja cin.ignore() tyhjentavat kentan ja siirtyvat eteenpain
					cin.ignore(10000, '\n');
					cout << "Syota vain lukuja: ";
				}
			} while (!toiminto);
			switch (toiminto) {
			case 1:
				asiakas[asiakasLaskin] = luoAsiakas(huoneet, huoneidenMaara, asiakasLaskin);
				asiakas[asiakasLaskin].alennusPros = arvoAlennus();
				asiakas[asiakasLaskin].lopullinenHinta = asiakas[asiakasLaskin].hinta - (asiakas[asiakasLaskin].hinta * (asiakas[asiakasLaskin].alennusPros / 100));
				asiakasLaskin++;
				for (int i = 1; i < asiakasLaskin; i++) { // TaSSa TaYTETaaN huoneet[] TAULUA
					huoneet[asiakas[i].huoneNumero] = true;
				}
				system("CLS");
				break;
			case 2:
				for (int i = 1; i < asiakasLaskin; i++) {
					cout << "Asiakkaan nimi:\t\t" << asiakas[i].nimi << endl;
					cout << "Oiden maara:\t\t" << asiakas[i].yomaara << endl;
					cout << "Huoneen tyyppi:\t\t" << asiakas[i].huoneTyyppi << endl;
					cout << "Hinta:\t\t\t" << asiakas[i].hinta << endl;
					cout << "Alennus prosentti:\t" << asiakas[i].alennusPros << endl;
					cout << "Lopullinen hinta:\t" << asiakas[i].lopullinenHinta << endl;
					asiakas[i].varausnumero = varausnumeroTaulu[i]; // Sijoitetaan varausnumeroGeneraattori() funktiolla arvottu varausnumero
																	// Asiakas structin vastaavaan kenttaan
					cout << "Varausnumero:\t\t" << asiakas[i].varausnumero << endl;
					cout << "Huoneen numero:\t\t" << asiakas[i].huoneNumero << endl << endl;
				}
				break;
			case 3:
				for (int i = 0; i < huoneidenMaara; i++) {
					cout << huoneet[i] << " ";
					t++;
					if (t == 2) {
						cout << endl;
						t = 0;
					}
				}
				cout << endl;
				break;
			case 4:
				cout << "Anna nimesi siina muodossa kun olet syottanyt sen jarjestelmaan: ";
				cin.ignore(); 
				getline(cin, nimi); // Kysytaan kayttajan nimea

				for (int i = 1; i < asiakasLaskin; i++) { // Verrataan saatua syotetta kaikkiin olemissa oleviin asiakkaisiin
					if (asiakas[i].nimi == nimi) {        // Jos asiakas loytyy aloitetaan asiakkaan muokkaaminen, annetaan alemalla rivilla muokkaaAsiakas() funktiolle asiakkaan jo olemassa olevat tiedot
						asiakas[i] = muokkaaAsiakas(asiakas[i].nimi, asiakas[i].huoneTyyppi, asiakas[i].huoneNumero, asiakas[i].yomaara, huoneidenMaara, huoneet, asiakas[i].alennusPros);
						asiakas[i].lopullinenHinta = asiakas[i].hinta - (asiakas[i].hinta * (asiakas[i].alennusPros / 100)); // Lasketaan asiakkaalle tilauksen lopullinen hinta

					}
				}
				for (int i = 1; i < asiakasLaskin; i++) { 
					huoneet[asiakas[i].huoneNumero] = true; // Paivitetaan asiakkaan huone jos asiakas vaihtaa huoneen tyyppia
				}
				break;
			}
		}
		else {
			cout << "Valitettavasti hotellissa ei ole vapaita huoneita";
			toiminto = 5;
		}
	} while (toiminto != 5);
	return EXIT_SUCCESS;
}

void varausnumeroGeneraattori(int vnumeroTaulu[], int asiakasMaara) {
	bool uusiLuku; // Alustetaan bool muuttuja
	for (int i = 0; i < asiakasMaara; i++) { // Luodaan asiakkaiden maximi maaran verran uniikkeja varausnumeroita
		do {
			int num1 = rand() % 9 + 1; // Arvotaan viidelle eri muuttujalle arvo 1 ja 9 valilta
			int num2 = rand() % 9 + 1;
			int num3 = rand() % 9 + 1;
			int num4 = rand() % 9 + 1;
			int num5 = rand() % 9 + 1;

			string s1 = to_string(num1); // Muutetaan ylempana arvotut int muuttujat string muotoon
			string s2 = to_string(num2);
			string s3 = to_string(num3);
			string s4 = to_string(num4);
			string s5 = to_string(num5);

			string s = s1 + s2 + s3 + s4 + s5; // Yhdistetaan arvotut luvut yhdeksi luvuksi ( 1 + 2 + 3 = 123 )

			int vNumero = stoi(s); // Muutetaan yhdistetty luku takaisin string muodosta int muotoon
			vnumeroTaulu[i] = vNumero; // Sijoitetaan arvottu luku varausnumero tauluun

			uusiLuku = true;
			for (int j = 0; j < i; j++) { // Aloitetaan for loop joka looppaa asiakkaiden maksimi maaran mukaan
				if (vnumeroTaulu[j] == vnumeroTaulu[i]) { // Verrataan uutta arvottua lukua ( vnumeroTaulu[i] )
					uusiLuku = false;					  // Kaikkiin jo arvottuihin lukuihin ( vnumeroTaulu[j] )
				}										  // Jos arvottu luku on jo taulussa arpominen aloitetaan uudestaan
			}											  // Arvontaa suoritetaan siihen asti kun on arvottu 300 uniikkia lukua
		} while (!uusiLuku);
	}
}
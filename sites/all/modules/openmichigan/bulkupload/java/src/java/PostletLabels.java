/*	Copyright (C) 2005 Simon David Rycroft

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 2
	of the License, or (at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA. */
import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.net.URL;
import java.io.InputStreamReader;

public class PostletLabels {

	// languages listed by their two letter codes (http://www.w3.org/WAI/ER/IG/ert/iso639.htm)
	// The compiled in languages will be:
	// English
	// Spainish
	// Dutch
	// German
	// French
	// Italian
	// Portuguese

	// Current: EN, DE, NL, FR, ES, IT, NO, TU, FI
	private String [] language;

	private static final int numLabels = 17;

	private static final String [][] languages = {{
				"EN",
				"Filename",			//0
				"File Size",		//1
				"Finished",			//2
				"The destination URL provided is not a valid one.", //3
				"You have not provided a destination URL.",		 //4
				"Postlet error",	//5
				"Add",				//6
				"Remove",			//7
				"Upload",			//8
				"Help",				//9
				"Upload progress:",	//10
				"Do not close your web browser, or leave this page until upload completes.", //11
				"Postlet warning",	//12
				"Image files",		//13
				"Select file for upload", //14
				"The help URL provided is not a valid one.",
				"The following files failed to upload"},
				{
				"DE",
				"Dateiname",//0
				"Dateigröße",//1
				"Fertig",
				"Die angegebene Ziel-URL ist ungültig.",
				"Es ist keine Ziel-URL angegeben.",
				"Postlet Fehler",
				"Hinzufügen",
				"Entfernen",
				"Upload",
				"Hilfe",
				"Upload prozess:",
				"Der Browser darf nicht geschlossen werden solange der Upload läuft.",
				"Postlet Warnung",
				"Bild-Dateien",
				"Datei zum hochladen auswählen",
				"Die angegebene Hilfe-URL ist nicht gültig.",
				"The following files failed to upload"},
				{
				"NL",
				"Bestands naam",
				"Bestands grootte",
				"Klaar",
				"De opgegeven doel URL is niet correct.",
				"U heeft geen doel URL opgegeven.",
				"Postlet fout",
				"Toevoegen",
				"Verwijder",
				"Upload",
				"Help",
				"Upload voortgang",
				"Uw web browser niet sluiten, of deze pagina verlaten tot dat de upload compleet is.",
				"Postlet waarschuwing",
				"Plaatjes bestanden",
				"Selecteer bestand voor upload",
				"De help URL is niet correct",
				"The following files failed to upload"},
				{
				"FR",
				"Nom de fichier", //0
				"Taille du fichier", //1
				"Terminé", //2
				"L'URL de destination fournie n'est pas valide.", //3
				"Vous n'avez pas fourni d'URL de destination.", //4
				"Erreur Postlet", //5
				"Ajouter", //6
				"Enlever", //7
				"Envoyer", //8
				"Aide", //9
				"Progression de l'envoi:", //10
				"Ne fermer pas votre browser et rester sur cette page jusqu'à l'envoi complet des données.", //11
				"Avertissement Postlet", //12
				"Fichiers image", //13
				"Selectionner les fichiers à envoyer", //14
				"L'URL de l'aide fournie n'est pas valide.",
				"The following files failed to upload"},
				{
				"ES",
				"Fichero",			//0
				"Tamaño",			//1
				"Terminado",		//2
				"La URL destino no es válida.", //3
				"No hay una URL destino especificada.",		 //4
				"Postlet error",	//5
				"Añadir",			//6
				"Quitar",			//7
				"Subir",			//8
				"Ayuda",			//9
				"Progreso de la transferencia:",	 //10
				"No cerrar el navegador o esta ventana hasta que la transferencia haya terminado.", //11
				"Aviso del Postlet",//12
				"Ficheros de imágenes",//13
				"Selecciona los ficheros para subir", //14
				"La URL de ayuda no es válida.",
				"The following files failed to upload"},
				{
				"IT",
				"Nome File",//0
				"Dimensione File",//1
				"Terminato",//2
				"L'indirizzo fornito non è valido.",//3
				"Non hai inserito un indirizzo di destinazione.",//4
				"Errore di Postlet",//5
				"Aggiungi",//6
				"Rimuovi",//7
				"Trasferisci",//8
				"Help",//9
				"Stato del trasferimento",//10
				"Non chiudere il browser o cambiare pagina finché il trasferimento non è finito.",//11
				"Avvertimento di Postlet",//12
				"File immagine",//13
				"Seleziona il file da trasferire",//14
				"L'indirizzo dell'help non è valido.",
				"The following files failed to upload"},
				{
				"NO",
				"Filnavn",
				"Fil størrelse",
				"Ferdig",
				"Den URL du oppgav er ikke gyldig.",
				"Du har ikke oppgitt en URL.",
				"Postlet feil",
				"Legg til",
				"Ta bort",
				"Last opp",
				"Hjelp",
				"Upload gjennomføring:",
				"Lukk ikke igjen denne nettsiden, eller forlate nettsiden før opplastingen er ferdig.",
				"Postlet advarsel",
				"Bildefiler",
				"Velg fil for opplasting",
				"Den angitte hjelp URL er ikke gyldig.",
				"The following files failed to upload"},
				{
				"FI",
				"Tiedoston nimi",
				"Tiedoston koko",
				"Valmis",
				"URL-osoitetta ei löydy",
				"Kirjoita URL-osoite",
				"Postlet -virhe",
				"Lisää",
				"Poista",
				"lataa",
				"Help",
				"Lataaminen käynnissä",
				"Älä sulje selainta tai poistu sivuilta ennen kuin lataaminen on päättynyt.",
				"Postlet -varoitus",
				"Kuvatiedostot",
				"Valitse tiedosto, jonka aiot ladata",
				"Help-toiminnon URL-osoitetta ei löydy.",
				"The following files failed to upload"},
				{
				"TU",
				"Dosya Adý",
				"Dosya Boyutu",
				"Bitti",
				"Yazdýðýnýz URL desteklenen bir URL deðil!",
				"Belirtilmiþ (desteklenen) bir URL niz yok!",
				"Postlet Hatasý",
				"Ekle",
				"Kaldýr",
				"Yükle",
				"Yardým",
				"Yükleme Süreci",
				"Yükleme bitene kadar bu sayfayý kapatmayýn veya ayrýlmayýn.",
				"Postlet uyarýsý",
				"Resim (imaj) dosyalarý",
				"Yükleme için dosya seçin",
				"The help URL provided is not a valid one.",
				"The following files failed to upload"},
				{
				"EMPTY",
				"",
				"",
				"",
				"",
				"",
				"",
				"",
				"",
				"",
				"",
				"",
				"",
				"",
				"",
				"",
				"",
				""}}; //15

	/** Creates a new instance of PostletLabels */
	public PostletLabels(String l, URL codeBase) {
		boolean languageIncluded = false;
		for (int i=0; i<languages.length; i++){
			if (languages[i][0].equalsIgnoreCase(l)){
				languageIncluded = true;
				language = languages[i];
				break;
			}
		}
		if (!languageIncluded)
			readUserDefinedLanguageFile(codeBase, l);
	}

	public String getLabel(int i){
		if (i >= numLabels)
			return "ERROR!";
		return language[i+1];
	}
	// Method reads a standard named file, from the server (same directory as the
	// jar file), and sets the labels from this.
	private void readUserDefinedLanguageFile(URL codeBase, String lang){
		try {
			URL languageURL = new URL(codeBase.getProtocol()+"://"+codeBase.getHost()+codeBase.getPath()+"language_"+lang.toUpperCase().trim());
			BufferedReader in = new BufferedReader(new InputStreamReader(languageURL.openStream()));
			language = new String [numLabels];
			for (int i=0; i<numLabels; i++)
				language[i]=in.readLine();
		}
		catch (FileNotFoundException fnf){
			// File not found, default used instead.
			language = languages[0];
		}
		catch (IOException ioe){
			// File probably too short.
			language = languages[0];
			System.out.println("Language file possibly too short, please ensure it has 18 lines, terminated by a final carriage return");
		}
	}
}

# OpenCV Tutorials for Introduction to Digital Image Processing

A series of ten C++/OpenCV tutorials written as teaching material for the Introduction to Digital Image Processing course. They cover image and video I/O, color spaces, histograms, edge detection, frequency-domain deblurring, template matching, morphology and watershed segmentation, shape descriptors, camera calibration, and SIFT/ORB local features. Each tutorial comes with its LaTeX source and runnable example programs. I wrote the tutorials and examples; the versions published on the course website were reviewed and edited by the course's teaching assistant.

> **Note:** Apart from this summary, everything in this project is written in Bosnian: the rest of this README, the source code, the comments and the technical documentation.

> **Napomena:** Izvorni kod, komentari i tehnička dokumentacija za ovaj projekat su napisani na bosanskom jeziku.

## O projektu

Tutorijali su napisani za predmet **Uvod u digitalnu obradu slike** na Elektrotehničkom fakultetu Univerziteta u Sarajevu (akademska 2022/2023. godina). Uvode osnovne klase i funkcije biblioteke OpenCV i pokazuju primjere njihove upotrebe, kako bi studenti lakše riješili laboratorijske vježbe i zadatke za samostalan rad. Pretpostavlja se osnovno poznavanje programskog jezika C++.

Autorica sam tutorijala i pratećih primjera u ovom repozitoriju. Verzije objavljene na stranici predmeta pregledao je i dopunio asistent na predmetu, pa se mogu razlikovati od verzija u ovom repozitoriju.

## Sadržaj tutorijala

| Tutorijal | Tema | Primjeri |
|---|---|---|
| **T1** | Uvod u OpenCV: klasa `cv::Mat`, prvi program, rad s video datotekama | `primjer1`–`primjer3` |
| **T2** | Pikseli unutar slike, manipulacija koordinatama, prostori boja, binarizacija | `primjer1`, `primjer2` |
| **T3** | Operacije u prostornom domenu: linearna i gama transformacija, histogrami, izjednačavanje histograma | `primjer1`–`primjer4` |
| **T4** | Detekcija ivica: Sobel i Canny operator | `primjer1`, `primjer2` |
| **T5** | Operacije u frekventnom domenu, uklanjanje zamućenja (*deblur*) | `primjer` |
| **T6** | Podudaranje predložaka (*template matching*) na fotografijama igraćih karata | `primjer1` |
| **T7** | Morfološke operacije i segmentacija metodom *watershed* | `primjer1` |
| **T8** | Deskriptori oblika: konture, klasifikacija po broju vrhova, cirkularnost, konveksnost, momenti | samo upute |
| **T9** | Kalibracija kamere i uklanjanje distorzije | `primjer` |
| **T10** | Lokalni deskriptori: SIFT i ORB, podudaranje ključnih tačaka | `primjer1` |

## Struktura repozitorija

Svaki tutorijal ima vlastiti direktorij (`T1`–`T10`) sa sljedećim sadržajem:

```
TN/
├── Tutorijal_N.pdf     # Prevedeni tutorijal (T10 ima samo LaTeX izvorni kod)
├── latex/              # LaTeX izvorni kod tutorijala (main.tex, ref.bib, Slike/)
├── primjerX/           # Primjeri programa (main.cpp, CMakeLists.txt)
└── *.jpg / *.jpeg      # Ulazne slike i rezultati primjera
```

Ulazne slike i rezultati nalaze se direktno u direktoriju tutorijala, jer ih primjeri učitavaju i snimaju putanjom `../ime_slike` u odnosu na direktorij u kojem se program pokreće. U direktoriju `T6/` nalaze se vlastite fotografije igraćih karata (`Moje karte/`) i odgovarajući predlošci (`Moje karte predlosci/`).

## Pokretanje primjera

**Preduslovi:** C++ kompajler s podrškom za C++11, CMake 3.14 ili noviji, biblioteka **OpenCV 4** i **Qt** (5 ili 6, modul *Core*). Primjeri su razvijeni u okruženju Qt Creator, ali se mogu prevesti i iz komandne linije.

Na Ubuntu sistemu:

```bash
sudo apt install build-essential cmake libopencv-dev qtbase5-dev
```

Primjer se prevodi u direktoriju pored izvornog koda, kako bi putanja `../` pokazivala na direktorij tutorijala s ulaznim slikama:

```bash
cd T3
cmake -S primjer1 -B build-primjer1
cmake --build build-primjer1
cd build-primjer1
./primjer1
```

U Qt Creatoru dovoljno je otvoriti `CMakeLists.txt` željenog primjera. Podrazumijevani *shadow build* direktorij nalazi se pored direktorija primjera, pa relativne putanje rade bez izmjena.

### Napomene o putanjama

Pojedini primjeri koriste apsolutne putanje s računara na kojem su razvijeni. Prije pokretanja ih je potrebno zamijeniti putanjom do vlastite slike ili videa:

- `T1/primjer1`, `T2/primjer1` i `T2/primjer2` učitavaju proizvoljnu fotografiju (u originalu `cat.jpeg`);
- `T1/primjer2` učitava proizvoljnu video datoteku (`.mp4`);
- `T9/primjer` koristi slike šahovske ploče za kalibraciju kamere.

## Prevođenje tutorijala

Tutorijali se prevode standardnom LaTeX distribucijom uz `biber`:

```bash
cd T1/latex
pdflatex main.tex
biber main
pdflatex main.tex
```

## Autor

- **Autorica tutorijala i primjera:** Berina Biberović
- **Predmet:** Uvod u digitalnu obradu slike, Elektrotehnički fakultet, Univerzitet u Sarajevu
- **Predmetni profesor:** prof. dr Emir Sokić

#include <opencv4/opencv2/core/mat.hpp>
#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/videoio.hpp>

int main() {

    // Ucitavanje videa u instancu klase cv::VideoCapture:
    cv::VideoCapture originalni_video("/home/anniberi/Documents/Fakultet/2. semestar/UDOS/Tutorijali/T1/video.mp4");

    // Varijabla tipa cv::Mat koju cemo koristiti za ucitavanje frejmova iz originalnog videa:
    cv::Mat frame;

    // Prikaz videa u novom prozoru:

    // Instance klase cv::VideoCapture se ponasaju slicno kao instance input streamova (std::cin):
    originalni_video >> frame;

    // Dokle god ucitavamo frameove, neka se vrti while petlja (dakle, dok ne dodjemo do kraja videa):
    while(!frame.empty()) {

        // Prikazujemo frame u novom prozoru:
        cv::imshow("Ucitani video", frame);

        // Ukoliko pritisnemo 'q' program izlazi iz petlje:
        if(cv::waitKey() == 'q') break;

        // Ucitaj novi frame:
        originalni_video >> frame;
    }

    // Zatvaramo video file ili kameru ovom naredbom:
    originalni_video.release();

    return 0;
}

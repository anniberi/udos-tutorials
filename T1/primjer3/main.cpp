#include <opencv4/opencv2/core/mat.hpp>
#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/videoio.hpp>

int main() {

    // Instanciranje objekta tipa cv::VideoCapture ali preko web kamere:
    cv::VideoCapture kamera(0);

    // Treba nam opet frame:
    cv::Mat frame;

    // Potrebna nam je sirina i visina videa za instanciranje novog tipa
    // za snimanje snimka sa kamere u datoteku:
    int sirina_videa = kamera.get(cv::CAP_PROP_FRAME_WIDTH);
    int visina_videa = kamera.get(cv::CAP_PROP_FRAME_HEIGHT);

    // Kako bismo mogli snimiti video sa kamere, potrebna nam je nova klasa:
    cv::VideoWriter snimak_sa_kamere("../snimak_sa_kamere.avi", cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 10, cv::Size(sirina_videa, visina_videa));

    // Ucitavanje narednog frame-a unutar uslova petlje i provjera da li je zadnji frame
    // U ovom kontekstu to nema smisla jer je u pitanju video koji se direktno sa
    // web kamere snima, ali moze se isto iskoristiti ako se ucitava video
    // iz datoteke:
    while(kamera >> frame, !frame.empty()) { // Koristenje sejtan operatora se ne preporucuje!

        // Upisivanje frame-a u novi snimak:
        snimak_sa_kamere.write(frame);

        // Prikaz trenutnog frame-a:
        cv::imshow("Trenutni frame", frame);

        // Ukoliko se pritisne "q", break-a se while petlja:
        if(cv::waitKey() == 'q') break;
    }

    // Slicno kao u prethodnom primjeru, iskoritimo .release() funkciju za
    // zatvaranje videa:
    snimak_sa_kamere.release();
    kamera.release();

    return 0;
}

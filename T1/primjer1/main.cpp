#include <opencv4/opencv2/imgcodecs.hpp>
#include <opencv4/opencv2/core/mat.hpp>
#include <opencv4/opencv2/highgui.hpp>

int main() {

    // Deklaracija prve slike koju ucitavamo:
    cv::Mat prva_slika;

    // Ucitavanje prve slike:
    prva_slika = cv::imread("/home/anniberi/Pictures/Wallpapers/cat.jpeg", cv::IMREAD_COLOR);

    // Prikaz prve slike u prozoru programa:
    cv::imshow("Prva ucitana slika", prva_slika);

    // Cekamo unos od korisnika da bismo prestali prikazivati sliku:
    while(cv::waitKey() != 'q');

    // Cuvanje prve slike na novoj lokaciji pod novim imenom:
    cv::imwrite("../prva_slika.jpeg", prva_slika);

    return 0;

}

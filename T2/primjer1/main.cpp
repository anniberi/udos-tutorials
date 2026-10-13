#include <opencv4/opencv2/core/mat.hpp>
#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/imgcodecs.hpp>
#include <opencv4/opencv2/imgproc.hpp>

int main() {

    // Ucitavanje BGR slike:
    cv::Mat BGR_slika = cv::imread("/home/anniberi/Pictures/Wallpapers/cat.jpeg", cv::IMREAD_COLOR);

    // Deklarisanje grayscale, binarne i HSV slike:
    cv::Mat gray_slika, bin_slika, HSV_slika;

    // Koristenje cv::cvtColor funkcije kako bismo dobili grayscale i HSV sliku:
    cv::cvtColor(BGR_slika, gray_slika, cv::COLOR_BGR2GRAY);
    cv::cvtColor(BGR_slika, HSV_slika, cv::COLOR_BGR2HSV);

    // Koristenje threshold funkcije kako bismo dobili binarnu sliku:
    cv::threshold(gray_slika, bin_slika, 120, 255, cv::THRESH_BINARY);

    // Prikaz svih slika:
    cv::imshow("BGR slika", BGR_slika);
    cv::imshow("Grayscale slika", gray_slika);
    cv::imshow("HSV slika", HSV_slika);
    cv::imshow("Binarna slika", bin_slika);

    cv::waitKey();

    return 0;
}

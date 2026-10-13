#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/core.hpp>
#include <opencv4/opencv2/imgproc.hpp>

int main() {

    // Ucitavanje slike:
    cv::Mat slika = cv::imread("../original.jpg", cv::IMREAD_COLOR);

    // Treba nam grayscale slika:
    cv::Mat grayscale;
    cv::cvtColor(slika, grayscale, cv::COLOR_BGR2GRAY);

    // Sad trebamo da izjednacimo histogram nad ovom slikom:
    cv::Mat izjednacena;
    cv::equalizeHist(grayscale, izjednacena);

    cv::imshow("Grayscale", grayscale);
    cv::imshow("Nakon izjednacenja histograma", izjednacena);

    cv::waitKey();

    cv::imwrite("../grayscale.jpg", grayscale);
    cv::imwrite("../izjednacena.jpg", izjednacena);

    return 0;
}

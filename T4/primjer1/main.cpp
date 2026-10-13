#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/core/mat.hpp>
#include <opencv4/opencv2/imgproc.hpp>

int main() {

    // Ucitavanje slike:
    cv::Mat slika = cv::imread("../nonaka_miho.jpg", cv::IMREAD_COLOR);

    // Prebacivanje u grayscale:
    cv::Mat gray;
    cv::cvtColor(slika, gray, cv::COLOR_BGR2GRAY);

    // Dodavanje blura na grayscale sliku:
    cv::Mat blur;
    cv::GaussianBlur(gray, blur, cv::Size(3, 3), 0, 0, cv::BORDER_DEFAULT);

    // Sobel:
    cv::Mat sobel;
    int ddepth = CV_8U;
    cv::Sobel(blur, sobel, ddepth, 0, 1, 3, 1, 0, cv::BORDER_DEFAULT);

    cv::imshow("Originalna", slika);
    cv::imshow("Blur", blur);
    cv::imshow("Nakon Sobela", sobel);

    cv::waitKey();

    cv::imwrite("../sobel.jpg", sobel);

    return 0;
}

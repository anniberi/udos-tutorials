#include <opencv4/opencv2/core/mat.hpp>
#include <opencv4/opencv2/imgproc.hpp>
#include <opencv4/opencv2/imgcodecs.hpp>
#include <opencv4/opencv2/highgui.hpp>

int main() {

    // Ucitavnanje slike u grayscale-u:
    cv::Mat slika = cv::imread("/home/anniberi/Pictures/Wallpapers/cat.jpeg", cv::IMREAD_GRAYSCALE);
    cv::Mat binarna;

    // Pravljenje trackbar-ova:
    cv::namedWindow("Trackbars");
    cv::createTrackbar("Threshold 1", "Trackbars", nullptr, 255);
    cv::createTrackbar("(Block size - 3) / 2", "Trackbars", nullptr, 255);
    cv::namedWindow("Adaptivni thresholding");
    cv::namedWindow("Originalna grayscale slika");

    int t1, t2;

    do {

        // Ucitavanje t1 i t2 sa trackbarova:
        t1 = cv::getTrackbarPos("Threshold 1", "Trackbars");
        t2 = cv::getTrackbarPos("(Block size - 3) / 2", "Trackbars");

        // Sada primjenjujemo funkciju za adaptivni thresholding:
        cv::adaptiveThreshold(slika, binarna, 255, cv::ADAPTIVE_THRESH_MEAN_C, cv::THRESH_BINARY, 2 * t2 + 3, t1);
        // Prikaz slika:
        cv::imshow("Originalna grayscale slika", slika);
        cv::imshow("Adaptivni thresholding", binarna);

    }while(cv::waitKey() != 'q');

    cv::destroyAllWindows();

    cv::imwrite("../binarna.jpg", binarna);
    cv::imwrite("../originalna.jpg", slika);

    return 0;
}

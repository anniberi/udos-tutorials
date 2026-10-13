#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/core/mat.hpp>
#include <opencv4/opencv2/imgproc.hpp>

int main() {

    // Ucitavanje slike u grayscale-u:
    cv::Mat gray = cv::imread("../nonaka_miho.jpg", cv::IMREAD_GRAYSCALE);

    // Canny transformacija:
    cv::Mat canny;
    int t1, t2, aperture = 3;

    cv::namedWindow("Trackbars");
    cv::createTrackbar("Threshold 1", "Trackbars", nullptr, 255);
    cv::createTrackbar("Threshold 2", "Trackbars", nullptr, 255);

    do {

        // Uzimamo vrijednosti t1 i t2 preko trackbarova:
        t1 = cv::getTrackbarPos("Threshold 1", "Trackbars");
        t2 = cv::getTrackbarPos("Threshold 2", "Trackbars");

        cv::Canny(gray, canny, t1, t2, aperture, false);
        cv::imshow("Canny - aperture = 3", canny);
        cv::imshow("Grayscale slika", gray);

    }while(cv::waitKey() != 'q');

    return 0;
}

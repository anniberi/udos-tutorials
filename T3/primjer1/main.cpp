#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/core/mat.hpp>
#include <opencv4/opencv2/core/saturate.hpp>

int main() {

    // Ucitavanje originalne slike:
    cv::Mat original = cv::imread("../maca.jpeg");

    // Kreiranje nove slike:
    cv::Mat nova = cv::Mat::zeros(original.size(), original.type());

    // Parametri alpha i beta:
    double alpha = 1;
    int beta = 70;

    // Transformiranje svakog piksela g(i, j) = alpha * f (i, j) + beta:
    for(int i = 0; i < original.rows; i++) {
        for(int j = 0; j < original.cols; j++) {
            // Slika original je tipa BGR, tako da je i nova tipa BGR - imamo tri kanala za svaki element!
            for(int k = 0; k < original.channels(); k++) {
                nova.at<cv::Vec3b>(i, j)[k] = cv::saturate_cast<uchar>(alpha * original.at<cv::Vec3b>(i, j)[k] + beta);
            }
        }
    }

    // Prikaz originalne slike i nove slike:
    cv::imshow("Originalna slika", original);
    cv::imshow("Nova slika", nova);

    cv::waitKey();

    return 0;
}

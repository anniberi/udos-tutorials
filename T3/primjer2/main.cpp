#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/core.hpp>
#include <opencv4/opencv2/imgproc.hpp>

int main() {

    // Ucitavanje originalne slike:
    cv::Mat original = cv::imread("../maca2.jpg");
    cv::resize(original, original, cv::Size(), 0.2, 0.2);

    // Kreiranje nove slike:
    cv::Mat linearna = cv::Mat::zeros(original.size(), original.type());

    // Parametri alpha i beta:
    double alpha = 1.3;
    int beta = 40;

    // Transformiranje svakog piksela g(i, j) = alpha * f (i, j) + beta:
    original.convertTo(linearna, -1, alpha, beta);

    // Sada koristimo gamma transformaciju:
    double gamma = 0.35;
    cv::Mat lookUpTable(1, 256, CV_8U);
    uchar *p = lookUpTable.ptr();
    for(int i = 0; i < 256; i++)
        p[i] = cv::saturate_cast<uchar>(cv::pow((i / 255.0), gamma) * 255.0);

    cv::Mat gama_transf = original.clone();
    cv::LUT(original, lookUpTable, gama_transf);

    // Prikaz originalne slike i nove slike:
    cv::imshow("Originalna slika", original);
    cv::imshow("Linerana transformacija", linearna);
    cv::imshow("Gama transformacija", gama_transf);

    cv::waitKey();

    cv::imwrite("../original.jpg", original);
    cv::imwrite("../linearna.jpg", linearna);
    cv::imwrite("../gama.jpg", gama_transf);

    return 0;
}

#include <opencv4/opencv2/imgcodecs.hpp>
#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/imgproc.hpp>
#include <opencv4/opencv2/core.hpp>

int main() {

    // Ucitavanje ulazne slike:
    cv::Mat slika = cv::imread("../Moje karte/IMG_0007.JPG", cv::IMREAD_COLOR);
    // Ucitavanje predloska:
    cv::Mat temp = cv::imread("../Moje karte predlosci/tref.JPG", cv::IMREAD_COLOR);

    cv::Mat rezultat;

    // Ove varijable su nam potrebne za funkciju za template matching:
    int rezcol, rezrow;
    rezcol = slika.cols - temp.cols + 1;
    rezrow = slika.rows - temp.rows + 1;

    rezultat.create(rezrow, rezcol, CV_32FC1);

    cv::matchTemplate(slika, temp, rezultat, cv::TM_CCORR_NORMED);

    // Sad racunamo koliko se podudaraju i gdje:
    double min_vr, max_vr;
    cv::Point min_lok, max_lok, match_lok;

    cv::minMaxLoc(rezultat, &min_vr, &max_vr, &min_lok, &max_lok);
    match_lok = max_lok;

    // Sad trebamo nacrtati gdje je template nadjen:
    cv::rectangle(slika, match_lok, cv::Point(match_lok.x + temp.cols, match_lok.y + temp.rows), cv::Scalar(0, 0, 255), 2, 8, 0);

    cv::imshow("Rezultat template matchinga", slika);
    cv::waitKey();

    cv::imwrite("../rezultat.jpg", slika);

    return 0;
}

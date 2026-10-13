#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/core.hpp>
#include <opencv4/opencv2/imgproc.hpp>
#include <opencv4/opencv2/imgcodecs.hpp>
#include <opencv4/opencv2/core/fast_math.hpp>
#include <vector>

int main() {

    // Ucitavanje slike kojoj trazimo histogram:
    cv::Mat slika = cv::imread("../izjednacena.jpg", cv::IMREAD_GRAYSCALE);

    // Razdvajanje slike na 3 kanala (B, G i R):
    //std::vector<cv::Mat> kanali;
    //cv::split(slika, kanali);

    // Kako radimo sa B, G i R prostorima, znamo da su njihove vrijednosti od 0 do 255:
    int histSize = 256;
    float range[] = {0, 256};
    const float* histRange[] = {range};

    cv::Mat b_hist, g_hist, r_hist;

    // Postoji funkcija u OpenCV-u koja nam racuna histogram:
    cv::calcHist(&slika, 1, 0, cv::Mat(), b_hist, 1, &histSize, histRange, true, false);
    //cv::calcHist(&kanali[1], 1, 0, cv::Mat(), g_hist, 1, &histSize, histRange, true, false);
    //cv::calcHist(&kanali[2], 1, 0, cv::Mat(), r_hist, 1, &histSize, histRange, true, false);

    // Treba napraviti sliku koja ce prikazati histograme za B, G i R:
    int hist_sirina = 512, hist_visina = 400;
    int bin_sirina = cvRound((double) hist_sirina / histSize );
    cv::Mat histogramSlike(hist_visina, hist_sirina, CV_8UC3, cv::Scalar(255, 255, 255));

    // Prije iscrtavanja histograma, potrebno je normalizirati svaki histogram tako da vrijednosti
    // upadaju u opseg parametara koje smo naveli:
    cv::normalize(b_hist, b_hist, 0, histogramSlike.rows, cv::NORM_MINMAX, -1, cv::Mat());
    //cv::normalize(g_hist, g_hist, 0, histogramSlike.rows, cv::NORM_MINMAX, -1, cv::Mat());
    //cv::normalize(r_hist, r_hist, 0, histogramSlike.rows, cv::NORM_MINMAX, -1, cv::Mat());

    // Crtanje histograma tako sto pristupamo binovima i crtamo vrijednosti:
    for(int i = 1; i < histSize; i++) {
        cv::line(histogramSlike, cv::Point(bin_sirina * (i - 1), hist_visina - cvRound(b_hist.at<float>(i - 1))),
                 cv::Point(bin_sirina * (i), hist_visina - cvRound(b_hist.at<float>(i))), cv::Scalar(0, 0, 0), 2, 8, 0);
        /*cv::line(histogramSlike, cv::Point(bin_sirina * (i - 1), hist_visina - cvRound(g_hist.at<float>(i - 1))),
                 cv::Point(bin_sirina * (i), hist_visina - cvRound(g_hist.at<float>(i))), cv::Scalar(0, 255, 0), 2, 8, 0);
        cv::line(histogramSlike, cv::Point(bin_sirina * (i - 1), hist_visina - cvRound(r_hist.at<float>(i - 1))),
                 cv::Point(bin_sirina * (i), hist_visina - cvRound(r_hist.at<float>(i))), cv::Scalar(0, 0, 255), 2, 8, 0);*/
    }

    // Prikaz slike i histograma te slike:
    cv::imshow("Slika", slika);
    cv::imshow("Histogram", histogramSlike);

    cv::waitKey();

    cv::imwrite("../histogram_izjednacene.jpg", histogramSlike);

    return 0;
}

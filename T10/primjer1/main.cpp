#include <opencv4/opencv2/core.hpp>
#include <opencv4/opencv2/imgproc.hpp>
#include <opencv4/opencv2/highgui.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/calib3d.hpp>
#include <vector>
#include <algorithm>

int main() {

    // Kreiranje pametnog pokazivaca na objekat tipa cv::SIFT:
    cv::Ptr<cv::SIFT> sift = cv::SIFT::create();

    // Ucitavanje slike:
    cv::Mat slika = cv::imread("../Slika1.jpg", cv::IMREAD_GRAYSCALE);
    cv::Mat sablon = cv::imread("../SablonAS.jpg", cv::IMREAD_GRAYSCALE);

    // Pravimo vektore za keypoints na slici i na sablonu:
    std::vector<cv::KeyPoint> keypoints_slika, keypoints_sablon;

    // Pravimo matricu za deskriptore i na slici i na sablonu:
    cv::Mat deskriptori_slika, deskriptori_sablon;

    // Samo pozovemo funkciju za racunanje keypoint-a i deskriptora:
    sift->detectAndCompute(slika, cv::noArray(), keypoints_slika, deskriptori_slika, false);
    sift->detectAndCompute(sablon, cv::noArray(), keypoints_sablon, deskriptori_sablon, false);

    // Sada pozivamo funkciju koja ce da nacrta keypoints na slici i na sablonu:
    cv::Mat pomocna_slika, pomocni_sablon;
    cv::drawKeypoints(slika, keypoints_slika, pomocna_slika, cv::Scalar::all(-1), cv::DrawMatchesFlags::DEFAULT);
    cv::drawKeypoints(sablon, keypoints_sablon, pomocni_sablon, cv::Scalar::all(-1), cv::DrawMatchesFlags::DEFAULT);

    // Prikaz izvadjenih keypoint-a:
    cv::imshow("Keypoints na slici", pomocna_slika);
    cv::imshow("Keypoints na sablonu", pomocni_sablon);
    cv::waitKey();

    // Potrebno je naci koji deskriptori se podudaraju za ulaznu sliku i za sablon:
    cv::BFMatcher matcher(cv::NORM_L2);
    std::vector<cv::DMatch> matches;

    matcher.BFMatcher::match(deskriptori_sablon, deskriptori_slika, matches);

    // Sada gledamo koliko su koji matchevi "udaljeni":
    double max_udaljenost;
    std::vector<double> udaljenosti;

    for(int i  = 0; i < matches.size(); i++)
        udaljenosti.push_back(matches.at(i).distance);

    // Pronadjemo najvecu udaljenost dva matcha:
    max_udaljenost = *std::max_element(udaljenosti.begin(), udaljenosti.end());

    // Postavimo threshold za matcheve na osnovu max_udaljenost:
    double k = 0.1;
    double threshold = k * max_udaljenost;

    // Sada upisujemo sve matcheve koji su ispod thresholda u novi vektor za podudaranja:
    std::vector<cv::DMatch> podudaranja;

    for(int i = 0; i < matches.size(); i++)
        if(udaljenosti.at(i) <= threshold)
            podudaranja.push_back(matches.at(i));

    // Na kraju crtamo sva podudaranja koju su bila ispod gore navedenog thresholda:
    cv::Mat pomocna_slika2;
    cv::drawMatches(sablon, keypoints_sablon, slika, keypoints_slika, podudaranja, pomocna_slika2, cv::Scalar::all(-1), cv::Scalar::all(-1), std::vector<char>(), cv::DrawMatchesFlags::DEFAULT);

    cv::imshow("Rezultat", pomocna_slika2);
    cv::waitKey();

    cv::imwrite("../konacni.jpg", pomocna_slika2);

    return 0;
}

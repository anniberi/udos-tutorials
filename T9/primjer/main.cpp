#include <iostream>
#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/imgproc.hpp>
#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/core/mat.hpp>
#include <opencv4/opencv2/imgcodecs.hpp>
#include <opencv4/opencv2/core/matx.hpp>
#include <opencv2/calib3d.hpp>
#include <string>
#include <vector>

void pronadjiCoskove(cv::Mat &slika, std::vector<cv::Point2f> &corners) {

    // Pise da je ovaj parametar interior number of corners:
    cv::Size pattern_size(9, 6);
    // Funkcija za pronalazak vrhova:
    bool pronadjen = cv::findChessboardCorners(slika, pattern_size, corners,  cv::CALIB_CB_ADAPTIVE_THRESH + cv::CALIB_CB_NORMALIZE_IMAGE);
    if(pronadjen)
        cv::drawChessboardCorners(slika, pattern_size, cv::Mat(corners), pronadjen);
    cv::imshow("Slika chessboard-a", slika);
    cv::waitKey();
    cv::TermCriteria termcrit(cv::TermCriteria::COUNT|cv::TermCriteria::EPS,20,0.03);
    cv::cornerSubPix(slika, corners, cv::Size(11, 11), cv::Size(-1, -1), termcrit);


}

int main() {

    std::vector<cv::Point3f> objp;

    // Definiramo world coordinates za 3d tacke:
    for(int i = 0; i < 6; i++)
        for(int j = 0; j < 9; j++)
            objp.push_back(cv::Point3f(j, i, 0));

    // Parametri koji mi trebaju za cv::calibrateCamera:
    std::vector<std::vector<cv::Point3f>> object_points;
    std::vector<std::vector<cv::Point2f>> image_points;

    cv::Mat slika;
    int br = 1;

    while(br != 6) {

        std::string path = "/home/anniberi/Documents/Fakultet/2. semestar/UDOS/LV/Lab10/Prilog1/";
        std::string ime = std::to_string(br) + ".jpg";

        slika = cv::imread(path + ime, cv::IMREAD_GRAYSCALE);

        // Valjda funkcija da rezultat gdje su vrhovi u ovome:
        std::vector<cv::Point2f> corners;

        pronadjiCoskove(slika, corners);
        cv::imwrite("Rezultat_" + ime, slika);

        object_points.push_back(objp);
        image_points.push_back(corners);

        br++;

    }

    cv::destroyAllWindows();
    cv::Mat cameraMatrix, distCoeffs, R, T;

    cv::calibrateCamera(object_points, image_points, cv::Size(slika.rows, slika.cols), cameraMatrix, distCoeffs, R, T);

    std::cout << "Matrica kamere: " << cameraMatrix << std::endl;
    std::cout << "Koeficijenti distance: " << distCoeffs << std::endl;
    std::cout << "Rotacijski vektor: " << R << std::endl;
    std::cout << "Translacijski vektor: " << T << std::endl;

    cv::Mat pomocna;
    slika = imread("/home/anniberi/Documents/Fakultet/2. semestar/UDOS/LV/Lab10/Prilog1/1.jpg", cv::IMREAD_GRAYSCALE);
    cv::undistort(slika, pomocna, cameraMatrix, distCoeffs);

    cv::imshow("nema distorzije", pomocna);
    cv::imshow("ima distorzije", slika);
    cv::imwrite("bez_distorzije.jpg", pomocna);
    cv::imwrite("original.jpg", slika);
    cv::waitKey();

    return 0;

}

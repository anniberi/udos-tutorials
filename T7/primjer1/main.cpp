#include <iostream>
#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/imgproc.hpp>
#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/core/mat.hpp>
#include <opencv4/opencv2/imgcodecs.hpp>
#include <opencv4/opencv2/core/matx.hpp>
#include <string>
#include <vector>

cv::Mat originalna, gray, binarna, morfoloska_obrada, dilatacija, erozija, razlika, watershed;

int morph_operator = 0;
int morph_elem = 0;
int morph_size = 0;

int erosion_elem = 0;
int erosion_size = 0;
int dilation_elem = 0;
int dilation_size = 0;

int const max_operator = 4;
int const max_elem = 2;
int const max_kernel_size = 21;

std::string window_name = "Morfoloska transformacija";

void Morfoloske_Operacije(int, void*);
void Dilatacija(int, void*);
void Erozija(int, void*);

int main() {

    // Ucitaj originalnu sliku:
    originalna = cv::imread("../water_coins.jpg", cv::IMREAD_COLOR);
    gray = cv::imread("../water_coins.jpg", cv::IMREAD_GRAYSCALE);
    cv::threshold(gray, binarna, 0, 255, cv::THRESH_BINARY_INV + cv::THRESH_OTSU);

    cv::imshow("Originalna", originalna);
    cv::imshow("Binarna", binarna);
    cv::waitKey();

    cv::namedWindow(window_name, cv::WINDOW_AUTOSIZE);
    cv::createTrackbar("Operator:\n 0: Opening - 1: Closing  \n 2: Gradient - 3: Top Hat \n 4: Black Hat", window_name, &morph_operator, max_operator, Morfoloske_Operacije);
    cv::createTrackbar("Element:\n 0: Rect - 1: Cross - 2: Ellipse", window_name, &morph_elem, max_elem, Morfoloske_Operacije);
    cv::createTrackbar("Kernel size:\n 2n +1", window_name, &morph_size, max_kernel_size, Morfoloske_Operacije);

    Morfoloske_Operacije(0, 0);
    cv::waitKey(0);

    cv::namedWindow("Erozija - prikaz", cv::WINDOW_AUTOSIZE);

    cv::createTrackbar("Element:\n 0: Rect \n 1: Cross \n 2: Ellipse", "Erozija - prikaz", &erosion_elem, max_elem, Erozija);
    cv::createTrackbar("Kernel size:\n 2n +1", "Erozija - prikaz", &erosion_size, max_kernel_size, Erozija);

    Erozija(0, 0);
    cv::waitKey(0);

    cv::namedWindow("Dilatacija - prikaz", cv::WINDOW_AUTOSIZE);
    cv::moveWindow("Dilatacija - prikaz", morfoloska_obrada.cols, 0);
    cv::createTrackbar("Element:\n 0: Rect \n 1: Cross \n 2: Ellipse", "Dilatacija - prikaz", &dilation_elem, max_elem, Dilatacija);
    cv::createTrackbar("Kernel size:\n 2n +1", "Dilatacija - prikaz", &dilation_size, max_kernel_size, Dilatacija);

    Dilatacija(0, 0);
    cv::waitKey(0);


    cv::Mat konektovane(erozija.size(), CV_32S);
    int broj_komponenti = cv::connectedComponents(erozija, konektovane, 8, CV_32S);

    int sirina = konektovane.rows, duzina = konektovane.cols;
    int pix;

    for(int i = 0; i < sirina; i++) {
        for(int j = 0; j < duzina; j++) {
            pix = konektovane.at<int>(i, j);

            if(pix == 0) {
                pix = broj_komponenti;

                konektovane.at<int>(i, j) = pix;
            }

        }
    }

    for(int i = 0; i < sirina; i++) {
        for(int j = 0; j < duzina; j++) {
            auto pix1 = erozija.at<char>(i, j);
            auto pix2 = dilatacija.at<char>(i, j);

            if(pix1 != pix2) {
                konektovane.at<int>(i, j) = 0;
            }
        }
    }
    cv::watershed(originalna, konektovane);

    // Generate random colors:
    std::vector<cv::Vec3b> colors;
    for(int i = 0; i < broj_komponenti; i++) {
        int b = cv::theRNG().uniform(0, 256);
        int g = cv::theRNG().uniform(0, 256);
        int r = cv::theRNG().uniform(0, 256);

        colors.push_back(cv::Vec3b((uchar)b, (uchar)g, (uchar)r));
    }

    cv::Mat dst = cv::Mat::zeros(konektovane.size(), CV_8UC3);

    for(int i = 0; i < konektovane.rows; i++) {
        for(int j = 0; j < konektovane.cols; j++) {
            int index = konektovane.at<int>(i, j);
            if(index > 0 && index <= static_cast<int>(broj_komponenti)) {
                dst.at<cv::Vec3b>(i, j) = colors[index - 1];
            }
        }
    }

    cv::imshow("watershed", dst);
    cv::imwrite("../watershed_rezultat.jpg", dst);
    cv::imshow("originalna", originalna);
    cv::waitKey();
    return 0;
}

void Morfoloske_Operacije(int, void*) {
    int operation = morph_operator + 2;

    cv::Mat element = cv::getStructuringElement(morph_elem, cv::Size(2 * morph_size + 1, 2 * morph_size + 1), cv::Point(morph_size, morph_size));

    cv::morphologyEx(binarna, morfoloska_obrada, operation, element);

    cv::imshow(window_name, morfoloska_obrada);
}

void Dilatacija(int, void*) {
    int dilation_type = 0;
    if(dilation_elem == 0) dilation_type = cv::MORPH_RECT;
    else if(dilation_elem == 1) dilation_type = cv::MORPH_CROSS;
    else if(dilation_elem == 2) dilation_type = cv::MORPH_ELLIPSE;

    cv::Mat element = cv::getStructuringElement(dilation_type, cv::Size(2 * dilation_size + 1, 2 * dilation_size + 1), cv::Point(dilation_size, dilation_size));

    cv::dilate(erozija, dilatacija, element);
    cv::imshow("Dilatacija - prikaz", dilatacija);
}

void Erozija(int, void*) {
    int erosion_type = 0;
    if(erosion_elem == 0) erosion_type = cv::MORPH_RECT;
    else if(erosion_elem == 1) erosion_type = cv::MORPH_CROSS;
    else if(erosion_elem == 2) erosion_type = cv::MORPH_ELLIPSE;

    cv::Mat element = cv::getStructuringElement(erosion_type, cv::Size(2 * erosion_size + 1, 2 * erosion_size + 1), cv::Point(erosion_size, erosion_size));

    cv::erode(morfoloska_obrada, erozija, element);
    cv::imshow("Erozija - prikaz", erozija);
}

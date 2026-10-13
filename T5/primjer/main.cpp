#include <string>
#include <opencv4/opencv2/imgproc.hpp>
#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/core/mat.hpp>
#include <opencv4/opencv2/imgcodecs.hpp>
#include <opencv4/opencv2/core/matx.hpp>


// Odabrati jednu od funkcija.
void calcPSF(cv::Mat& outputImg, cv::Size filterSize, int len, double theta) {	// Linear motion
    cv::Mat h(filterSize, CV_32F, cv::Scalar(0));
    cv::Point point(filterSize.width / 2, filterSize.height / 2);
    cv::ellipse(h, point, cv::Size(0, cvRound(float(len) / 2.0)), 90.0 - theta, 0, 360, cv::Scalar(255), cv::FILLED);
    cv::Scalar summa = sum(h);
    cv::namedWindow("FILTER", cv::WINDOW_NORMAL);
    imshow("FILTER", h);
    outputImg = h / summa[0];
}


// Pogledati https://docs.opencv.org/4.x/d8/d01/tutorial_discrete_fourier_transform.html
void fftshift(const cv::Mat& inputImg, cv::Mat& outputImg) {
    outputImg = inputImg.clone();
    int cx = outputImg.cols / 2;
    int cy = outputImg.rows / 2;
    cv::Mat q0(outputImg, cv::Rect(0, 0, cx, cy));
    cv::Mat q1(outputImg, cv::Rect(cx, 0, cx, cy));
    cv::Mat q2(outputImg, cv::Rect(0, cy, cx, cy));
    cv::Mat q3(outputImg, cv::Rect(cx, cy, cx, cy));
    cv::Mat tmp;
    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);
    q1.copyTo(tmp);
    q2.copyTo(q1);
    tmp.copyTo(q2);
}

void filter2DFreq(const cv::Mat& inputImg, cv::Mat& outputImg, const cv::Mat& H) {
    cv::Mat planes[2] = { cv::Mat_<float>(inputImg.clone()), cv::Mat::zeros(inputImg.size(), CV_32F) };
    cv::Mat complexI;
    merge(planes, 2, complexI);
    dft(complexI, complexI, cv::DFT_SCALE);
    cv::Mat planesH[2] = { cv::Mat_<float>(H.clone()), cv::Mat::zeros(H.size(), CV_32F) };
    cv::Mat complexH;
    cv::merge(planesH, 2, complexH);
    cv::Mat complexIH;
    cv::mulSpectrums(complexI, complexH, complexIH, 0);
    cv::idft(complexIH, complexIH);
    cv::split(complexIH, planes);
    outputImg = planes[0];
}

void calcWnrFilter(const cv::Mat& input_h_PSF, cv::Mat& output_G, double nsr) {
    cv::Mat h_PSF_shifted;
    fftshift(input_h_PSF, h_PSF_shifted);
    cv::Mat planes[2] = { cv::Mat_<float>(h_PSF_shifted.clone()), cv::Mat::zeros(h_PSF_shifted.size(), CV_32F) };
    cv::Mat complexI;
    cv::merge(planes, 2, complexI);
    cv::dft(complexI, complexI);
    cv::split(complexI, planes);
    cv::Mat denom;
    pow(abs(planes[0]), 2, denom);
    denom += nsr;
    cv::divide(planes[0], denom, output_G);
};

void edgetaper(const cv::Mat& inputImg, cv::Mat& outputImg, double gamma, double beta) {
    int Nx = inputImg.cols;
    int Ny = inputImg.rows;
    cv::Mat w1(1, Nx, CV_32F, cv::Scalar(0));
    cv::Mat w2(Ny, 1, CV_32F, cv::Scalar(0));
    float* p1 = w1.ptr<float>(0);
    float* p2 = w2.ptr<float>(0);
    float dx = float(2.0 * CV_PI / Nx);
    float x = float(-CV_PI);
    for (int i = 0; i < Nx; i++) {
        p1[i] = float(0.5 * (tanh((x + gamma / 2) / beta) - tanh((x - gamma / 2) / beta)));
        x += dx;
    }
    float dy = float(2.0 * CV_PI / Ny);
    float y = float(-CV_PI);
    for (int i = 0; i < Ny; i++) {
        p2[i] = float(0.5 * (tanh((y + gamma / 2) / beta) - tanh((y - gamma / 2) / beta)));
        y += dy;
    }
    cv::Mat w = w2 * w1;
    cv::multiply(inputImg, w, outputImg);
}

int main(){
    std::string ime = "slika.jpeg";
    cv::Mat slika;
    slika = imread("../" + ime, cv::IMREAD_GRAYSCALE);

    cv::Mat rezultat;

    // Srezati sliku na paran broj redova i kolona
    cv::Rect roi = cv::Rect(0, 0, slika.cols & -2, slika.rows & -2);

    // Računanje Wienerovog filtera
    cv::Mat Hw, h;

    cv::namedWindow("Trackbars", cv::WINDOW_NORMAL);
    cv::namedWindow("Izlaz", cv::WINDOW_NORMAL);

    cv::createTrackbar("t1", "Trackbars", nullptr, 500);
    cv::createTrackbar("t2", "Trackbars", nullptr, 180);
    cv::createTrackbar("t3", "Trackbars", nullptr, 1000);

    char keyPress;
    cv::Mat pomocna;
    while(true) {
        // 18 11 48 - daje dobre rezultate
        int t1 = cv::getTrackbarPos("t1", "Trackbars");
        int t2 = cv::getTrackbarPos("t2", "Trackbars");
        int t3 = cv::getTrackbarPos("t3", "Trackbars");

        calcPSF(h, roi.size(), t1, t2);
        calcWnrFilter(h, Hw, 1.0 / double(t3));

        slika.convertTo(slika, CV_32F);

        edgetaper(slika, pomocna, 10, 10);

        // Filtriranje
        filter2DFreq(pomocna(roi), rezultat, Hw);

        // Prikazivanje filtrirane slike
        rezultat.convertTo(rezultat, CV_8U);
        cv::normalize(rezultat, rezultat, 0, 255, cv::NORM_MINMAX);
        cv::imshow("Izlaz", rezultat);

        if(cv::waitKey() == 'q') break;
    }

    cv::imwrite("../Rezultat.jpeg", rezultat);
    return 0;
}

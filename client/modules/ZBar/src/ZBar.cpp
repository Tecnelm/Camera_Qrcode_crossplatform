
/**
 * @file ZBar.cpp
 * @author https://learnopencv.com/barcode-and-qr-code-scanner-using-zbar-and-opencv/
 * @brief
 * @version 0.1
 * @date 2022-11-13
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "ZBar.hpp"
#include "zbar.h"

namespace ZBar {
using namespace std;
using namespace cv;
using namespace zbar;

// Find and decode barcodes and QR codes
void decode(const Mat& im, vector<decodedObject>& decodedObjects)
{

    // Create zbar scanner
    ImageScanner scanner;

    // Configure scanner
    scanner.set_config(ZBAR_NONE, ZBAR_CFG_ENABLE, 1);

    // Convert image to grayscale
    Mat imGray;
    cvtColor(im, imGray, CV_BGR2GRAY);

    // Wrap image data in a zbar image
    Image image(im.cols, im.rows, "Y800", (uchar*)imGray.data, im.cols * im.rows);

    // Scan the image for barcodes and QRCodes
    int n = scanner.scan(image);

    // Print results
    for (Image::SymbolIterator symbol = image.symbol_begin(); symbol != image.symbol_end(); ++symbol) {
        decodedObject obj;

        obj.type = symbol->get_type_name();
        obj.data = symbol->get_data();

        // Print type and data
        cout << "Type : " << obj.type << endl;
        cout << "Data : " << obj.data << endl
             << endl;

        // Obtain location
        for (int i = 0; i < symbol->get_location_size(); i++) {
            obj.location.push_back(Point(symbol->get_location_x(i), symbol->get_location_y(i)));
        }

        decodedObjects.push_back(obj);
    }
}

// Display barcode and QR code location
void addBarcodeLocation(Mat& im, vector<decodedObject>& decodedObjects)
{
    // Loop over all decoded objects
    for (int i = 0; i < decodedObjects.size(); i++) {
        vector<Point> points = decodedObjects[i].location;
        vector<Point> hull;

        // If the points do not form a quad, find convex hull
        if (points.size() > 4)
            convexHull(points, hull);
        else
            hull = points;

        // Number of points in the convex hull
        int n = hull.size();

        for (int j = 0; j < n; j++) {
            line(im, hull[j], hull[(j + 1) % n], Scalar(255, 0, 0), 3);
        }
    }

    // Display results
    imshow("Results", im);
    waitKey(0);
}

}
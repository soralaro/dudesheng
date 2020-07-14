#include <iostream>
#include "opencv2/opencv.hpp"

#define setbit(x,y)     ( (x) |= (1<<(y)) )
#define clearbit(x,y)   ( (x) &=~(1<< (y)) )
#define getbit(x,y)     ( ((x) >> (y)) & 1 )

int zp1(uint16_t * dst,int size,uint8_t *src1,uint8_t *src2) {
    for (int i = 0; i < size; ++i) {
        dst[i] = 0;
        for (int j = 0; j < 8; ++j) {
            if (getbit(src1[i], j)) {
                setbit(dst[i], j << 1);
            }
            if (getbit(src2[i], j)) {
                setbit(dst[i], (j << 1) + 1);
            }
        }
    }
}
int uzp0(uint16_t* src, int size, uint8_t *dst1, uint8_t *dst2){
    if(size < 0 || !src || !dst1 || !dst2){
        std::cerr << "Invalid input parameters." <<std::endl;
        return -1;
    }
    uint8_t res1 = 0;
    uint8_t res2 = 0;

    for (int i = 0; i < size; ++i) {
        res1 = 0;
        res2 = 0;
        for (int j = 0; j < 16; ++j) {
            if(getbit(src[i],j)){
                if((j & 1) == 0){
                    setbit(res1,(j>>1));
                } else{
                    setbit(res2,(j>>1));
                }
            }
        }
        dst1[i] = res1;
        dst2[i] = res2;
    }
    return 0;
}


int uzp1(uint16_t* src, int size, uint8_t *dst1, uint8_t *dst2){
    if(size < 0 || !src || !dst1 || !dst2){
        std::cerr << "Invalid input parameters." <<std::endl;
        return -1;
    }
    uint8_t res1;
    uint8_t res2;
    uint16_t ruler;

    for (int i = 0; i < size; ++i) {
        res1 = 0;
        res2 = 0;
        ruler = 0x8000;
        for (int j = 8; j > 0 ; --j) {
            res1 = res1 | ((src[i] & ruler)>>j);
            ruler = ruler >> 1;
            res2 = res2 | ((src[i] & ruler)>>(j-1));
            ruler = ruler >> 1;
        }
        dst1[i] = res1;
        dst2[i] = res2;
    }
    return 0;
}



int main(int argc, char **argv) {
    if(argc<4)
    {
        std::cout<<"pathd,pathout,zip or uzip"<<std::endl;
        return -1;
    }

    std::string  pathd=argv[1];


    std::string  pathout=argv[2];
    std::string to_do=argv[3];
    if(to_do.compare("zip")==0) {
        std::string pre_path="/20190611180417.oni.";
        std::string end_path=".D.png";
        pathd+=pre_path;
        for (int i = 0; i < 1407; i++) {

            // cv::Mat mat = cv::imread(path, CV_LOAD_IMAGE_COLOR);
            std::string file_in = pathd + std::to_string(i) + end_path;
            cv::Mat matd16 = cv::imread(file_in, CV_LOAD_IMAGE_ANYDEPTH);
            if (matd16.empty()) {
                std::cout << "open file " << file_in << " fail!" << std::endl;
                return -1;
            }
            //std::cout << "height=" << matd16.size().height << " width=" << matd16.size().width;
            //std::cout << " depth=" << matd16.depth();
            //std::cout << " elemSize=" << matd16.elemSize() << std::endl;
            //std::cout << " dims=" << matd16.dims << std::endl;
            //std::cout << " channels=" << matd16.channels() << std::endl;
            cv::Mat matd8_1(matd16.size(), CV_8UC1);
            cv::Mat matd8_2(matd16.size(), CV_8UC1);
            uzp0((u_int16_t *) matd16.data, matd16.size().area(), matd8_1.data, matd8_2.data);
            //cv::imwrite("1.png", matd8_1);
            //cv::imwrite("2.png", matd8_2);
            cv::Mat mat1_2;
            cv::vconcat(matd8_1, matd8_2, mat1_2);
            cv::imwrite(pathout + "/" + std::to_string(i) + ".png", mat1_2);
        }
    }

    if(to_do.compare("uzip")==0) {
        for (int i = 0; i < 1407; i++) {
            std::string pre_path="/";
            std::string end_path=".png";
            std::string file_in = pathd + std::to_string(i) + end_path;
            cv::Mat matd8_1_2 = cv::imread(file_in, CV_LOAD_IMAGE_ANYDEPTH);
            if (matd8_1_2.empty()) {
                std::cout << "open file " << file_in << " fail!" << std::endl;
                return -1;
            }
            cv::Mat matd16(matd8_1_2.size().height/2,matd8_1_2.size().width, CV_16UC1);
            zp1((u_int16_t *)matd16.data,matd16.size().area(),matd8_1_2.data,matd8_1_2.data+matd16.size().area());
            cv::imwrite(pathout+"/"+"20190611180417.oni."+std::to_string(i)+".D.png",matd16);
            //std
        }
    }
    if(to_do.compare("test")==0) {
        std::string pre_path="/20190611180417.oni.";
        std::string end_path=".D.png";
        pathd+=pre_path;
        std::string file_in = pathd + std::to_string(0) + end_path;
        cv::Mat matd16 = cv::imread(file_in, CV_LOAD_IMAGE_ANYDEPTH);
        if (matd16.empty()) {
            std::cout << "open file " << file_in << " fail!" << std::endl;
            return -1;
        }
        //std::cout << "height=" << matd16.size().height << " width=" << matd16.size().width;
        //std::cout << " depth=" << matd16.depth();
        //std::cout << " elemSize=" << matd16.elemSize() << std::endl;
        //std::cout << " dims=" << matd16.dims << std::endl;
        //std::cout << " channels=" << matd16.channels() << std::endl;
        cv::Mat matd8_1(matd16.size(), CV_8UC1);
        cv::Mat matd8_2(matd16.size(), CV_8UC1);
        uzp0((u_int16_t *) matd16.data, matd16.size().area(), matd8_1.data, matd8_2.data);
        //cv::imwrite("1.png", matd8_1);
        //cv::imwrite("2.png", matd8_2);
        cv::Mat mat1_2;
        cv::vconcat(matd8_1, matd8_2, mat1_2);
        cv::imwrite(pathout + "/" + std::to_string(0) + ".png", mat1_2);
    }
//    std::string  pathc=argv[2];
//    cv::Mat matc = cv::imread(pathc,  CV_LOAD_IMAGE_COLOR);
//    if(matc.empty())
//    {
//        std::cout<<"open file "<<pathc<<" fail!"<<std::endl;
//        return  -1;
//    }

    return 0;
}
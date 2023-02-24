#include <iostream>
#include <string>
#include <vector>

using namespace std;

// UPC-A code validation logic was obtained from:
// https://www.youtube.com/watch?v=e6aR1k-ympo&ab_channel=InOneLesson

class CUpc {
    public:
        typedef enum tagBarcodeType
        {
            Unknown = -1,
            Standard = 0,
            WeighedItems = 2,
            Pharmacy = 3,
            Coupons = 5,
        } BarcodeType;

    public:
        CUpc(string sUpc);
        inline ~CUpc() {};

        inline BarcodeType GetType(){return(m_UpcType);};
        inline string ManufacturerCode(){return(m_sUpc.substr(1, 5));}
        inline string ProductCode(){return(m_sUpc.substr(6, 5));}

    private:
        string m_sUpc;
        BarcodeType m_UpcType;

        void Validate();
        void DecodeBarcodeType();
        void ModuloCheck();
        int ComputeSum(vector<int> & vPos);
        static bool IsAllDigits(string & str);
        static int NextTenMultiple(int num);
};

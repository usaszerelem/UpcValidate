#include "CUpc.h"

using namespace std;

int main()
{
    static vector<string> upcCodes {
        "051000012517", "036000291452",
        "013700206252", "076950450479",
        "032415096873", "012345678905"
        };

    cout << endl << "UPC-A code validator" << endl << endl;

    try
    {
        for (const string upCode : upcCodes)
        {
            CUpc upc(upCode);

            string sBarCodeType;

            switch(upc.GetType())
            {
                case CUpc::BarcodeType::Standard:
                    sBarCodeType = "Standard";
                    break;

                case CUpc::BarcodeType::WeighedItems:
                    sBarCodeType = "Weighed Items";
                    break;

                case CUpc::BarcodeType::Pharmacy:
                    sBarCodeType = "Pharmacy";
                    break;

                case CUpc::BarcodeType::Coupons:
                    sBarCodeType = "Coupons";
                    break;

                default:
                    throw "Internal Error - Unknown barcode type.";
            }

            cout << "Manufacturer: " << upc.ManufacturerCode() << endl;
            cout << "Product: " << upc.ProductCode() << endl;
            cout << "Barcode Type: " << sBarCodeType << endl << endl;
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << endl;
    }

    return (0);
}

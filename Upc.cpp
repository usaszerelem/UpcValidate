#include "CUpc.h"

/// @brief UPC code type 'A' validator. If the passed in UPC code fails
/// validation, an exception is thrown with the specific user actionable
/// error message
/// @param sUpc - string with the UP code
CUpc::CUpc(string sUpc)
{
    m_UpcType = BarcodeType::Unknown;
    m_sUpc = sUpc;
    Validate();
}

/// @brief Called from the constructor to validate the received UPC code
/// Exceptions are thrown in case validation problems are detected.
void CUpc::Validate()
{
    if (m_sUpc.length() != 12 || CUpc::IsAllDigits(m_sUpc) == false) {
        throw "UPC-A code must be 12 digits";
    }

    DecodeBarcodeType();
    ModuloCheck();
}

/// @brief Does the module check on the UPC number
void CUpc::ModuloCheck()
{
    vector<int> oddPos {1, 3, 5, 7, 9, 11};
    vector<int> evenPos {2, 4, 6, 8, 10};

    int nOddSum = ComputeSum(oddPos);
    int nEvenSum = ComputeSum(evenPos);

    int nSum = (3*nOddSum) + nEvenSum;
    int nMod = CUpc::NextTenMultiple(nSum) - nSum;

    char ch = m_sUpc[11];
    int nModule = int(ch - '0');

    if (nModule != nMod) {
        throw "Invalid modulo";
    }
}

/// @brief Computes the sum of all the values at the specified
/// UPC code positions
/// @param vPos - vector of integers containing the positions
/// @return sum of all the values at specified positions
int CUpc::ComputeSum(vector<int> & vPos)
{
    int nSum = 0;

    for (const int nPos : vPos)
    {
        // The -1 is needed because vPos holds
        // 1 based position numbers
        int idx = nPos;
        char ch = m_sUpc[idx - 1];
        nSum += int(ch - '0');
    }

    return(nSum);
}

/// @brief Finds the next multiple of 10 of the provided number
/// @param num - starting point to find the next multiple of 10
/// @return Computed number
int CUpc::NextTenMultiple(int num)
{
    if ((num % 10) != 0)
    {
        for (int i = 1; i < 10; i++)
        {
            if (((num + i) % 10) == 0)
            {
                num += i;
                break;
            }
        }
    }

    return(num);
}

/// @brief Helper function that ensures the UPC code string
/// contains only numbers
/// @param str - string to verify
/// @return Boolean validation
bool CUpc::IsAllDigits(string & str)
{
    return str.find_first_not_of("0123456789") == std::string::npos;
}

/// @brief Retrieves teh barcode type from the UPC code
void CUpc::DecodeBarcodeType()
{
    char ch = m_sUpc[0];
    int nType = int(ch - '0');

    switch(nType)
    {
        case BarcodeType::Standard:
            m_UpcType = BarcodeType::Standard;
            break;

        case BarcodeType::WeighedItems:
            m_UpcType = BarcodeType::WeighedItems;
            break;

        case BarcodeType::Pharmacy:
            m_UpcType = BarcodeType::Pharmacy;
            break;

        case BarcodeType::Coupons:
            m_UpcType = BarcodeType::Coupons;
            break;

        default:
            throw "Unrecognized Barcode type";
    }
}
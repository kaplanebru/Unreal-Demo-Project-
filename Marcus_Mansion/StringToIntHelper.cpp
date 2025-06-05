


#include "StringToIntHelper.h"

int32 UStringToIntHelper::ConvertStringToInt(const FString& InputString)
{
    if (InputString.Len() == 1 && FChar::IsDigit(InputString[0]))
    {
        return InputString[0] - '0'; // Convert ASCII character to integer
    }
    return -1; // Return -1 if the input is not a valid single-digit number
}
# CSV Reader Extended

CSV Reader Extended is a fast header-only CSV reader/parser. However is does support more function than only parsing classic CSV files.

Following features are provided in this library:

- Custom seperator
- CSV fields in CSV fields
- Optional CSV fields at the end
- Discard/Ignoring CSV fields
- Custom converters
- Custom string classes
- Custom readers

## Requirements ##

- C++11 support

This library successfully compiled on following compiler:

- Visual Studio 2015 Update 2
- MinGW 4.9.2

## Example ##

```cpp
#include <iostream>
#include "CSVReader.h"

int main()
{
    auto reader = CSVReader::MakeStringReader("This is a test,42,5\nHello,World");
    auto csv_reader = CSVReader::MakeCSVReaderFromBasicString(&reader, ',')
    
    try {
        std::string test_string;
        int answer;
        double five;
        std::string world_string;
        
        csv_reader
            .ReadDataLine(&test_string, &answer, &five)
            .ReadDataLine(CSVDiscard(), &world_string);
        
        std::cout << test_string << " " << answer << " " << five << " " << world_string << std::endl;
    } catch (const std::exception& err) {
        std::cout << "Error while parsing: " << err.what() << std::endl;
    }
}
```

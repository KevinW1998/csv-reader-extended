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

This library was successfully compiled on following compiler:

- Visual Studio 2015 Update 2
- MinGW 4.9.2
- GCC 4.8.1
- CLang 3.3

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
            .ReadDataLine(CSVReader::CSVDiscard(), &world_string);

        std::cout << test_string << " " << answer << " " << five << " " << world_string << std::endl;
    } catch (const std::exception& err) {
        std::cout << "Error while parsing: " << err.what() << std::endl;
    }
}
```

## Reference ##

### Creating a Reader ###
#### CSVReader::MakeStringReader ####
A reader, which parses a string.
##### Definition: #####
```cpp
template<class StrElementType, class StrElementTraits, class StrElementAlloc>
constexpr StringReader<StrElementType, StrElementTraits, StrElementAlloc> MakeStringReader(const std::basic_string<StrElementType, StrElementTraits, StrElementAlloc>& str)
```
str - A basic_string (std::string/std::wstring) containing text to parse

##### Example: #####
```cpp
auto reader = CSVReader::MakeStringReader("This is a test,42,5\nHello,World");
```
<br />
<br />


#### CSVReader::MakeIfStreamReader ####
A reader, which parses a input file stream.
##### Definition: #####
```cpp
template<class StrElementType, class StrElementTraits>
constexpr IfStreamReader<StrElementType, StrElementTraits> MakeIfStreamReader(std::basic_ifstream<StrElementType, StrElementTraits>* reader)
```
reader - A basic_ifstream (std::ifstream/std::wifstream) for reading out of a file stream.

##### Example: #####
```cpp
std::ifstream fileReader("test.csv", std::ios::in | std::ios::binary);
auto reader = CSVReader::MakeIfStreamReader(&fileReader);
```
<br />
<br />


#### CSVReader::MakeDirectReader ####
A direct reader, which reads out a string, but ignores any newlines.
##### Definition: #####
```cpp
template<class StrT>
constexpr DirectReader<StrT> MakeDirectReader(const StrT& data)
```
data - Any class, which represents a string.

##### Example: #####
```cpp
auto reader = CSVReader::MakeDirectReader("This is a test,42,5\nHello,World");
```
<br />
<br />


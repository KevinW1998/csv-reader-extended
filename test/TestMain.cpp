#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <catch.hpp>
#include <CSVReader.h>

TEST_CASE("Main Test", "[csv-reader]") {
    auto reader = CSVReader::MakeStringReader(std::string("This is a test,42,5\nHello,World"));
    auto csv_reader = CSVReader::MakeCSVReaderFromBasicString(&reader, ',');
     
    std::string test_string;
    int answer;
    double five;
    std::string world_string;

    csv_reader
        .ReadDataLine(&test_string, &answer, &five)
        .ReadDataLine(CSVReader::CSVDiscard(), &world_string);
}
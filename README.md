# Piosolver Hand Classification Program

The program takes [Piosolver's](https://www.piosolver.com/) aggregated-analysis csv file and categorizes the hand and board texture into a hand type. For example "AdAc" on "Kd7c3c" would be classified as an "overpair". The hand classifications are output into a separate csv file. Currently the program has some buggy hand categorizations for flops and does not output data for paired boards. Please refer to Hand_Classifier_Tests.cpp for validated hand categories. 

The CMakeLists.txt file works in CLion on Windows 8.1 and Ubuntu 16.04 and 18.04. The [fast-cpp-csv-parser library](https://github.com/ben-strasser/fast-cpp-csv-parser) is required. [Catch2](https://github.com/catchorg/Catch2) testing framework is included.  

In the R folder, there is a file "combine_csv.r" which requires the dplyr library. The function `read.cat()` will produce a dataframe from the two csv files. If no hand categorization csv file is given, the function will automatically search the current working directory for a file with the name "filenameHandCat.csv" and attempt to merge these files. The dataframe will also include a series of simpler hand categories which I have found useful in analysis. 

## Getting Started


```
mkdir build
cd build
cmake ../

```

```
./HandClassifier "/cygdrive/c/PioSOLVER/Reports/report_directory/report_file.csv"

```

## Running the tests
Tests run with the -t option. 

```
./HandClassifier dir/file -t

```
The tests validate most hand-board combos and are extensive, but not exhaustive. 


## Versioning

Currently in version 0.01 

## Authors

* **Tyler Forrester** - *Initial work* - [BillF1953](https://github.com/billf1953)


## License

Not sure which one is best yet. 




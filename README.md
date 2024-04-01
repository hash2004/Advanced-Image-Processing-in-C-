# Advanced Image Processing in C++

## Overview
This project is an extensive exploration of image processing techniques using C++, focusing on the conversion, manipulation, and analysis of images. Key features include the transformation of GIF images to PGM format, detailed image analysis, and efficient data structure utilization, including hashmaps and quad trees for optimized performance.

## Features

- **Image Conversion and Representation**: Initiates with converting GIF to PGM format, facilitating detailed grayscale image representation. The custom ADT class aids in storing and manipulating these images as arrays of pixel values.

- **Image Statistics and Manipulation**: Computes fundamental statistics like mean pixel value, count of black and white pixels, and average black pixels per row. It includes functions to read, save, and manipulate pixel values with robust error handling.

- **Negative Image Conversion**: An ADT class method inverts image colors, enabling alternative image analysis.

- **Connected Component Analysis**: Uses data structures like queues and stacks to identify and segregate connected components based on pixel connectivity, enhancing component analysis.

- **Data Structure Utilization**:
  - **Hashmaps**: For efficient data management and retrieval, enhancing performance in operations like connected component analysis.
  - **Quad Trees**: For spatial partitioning, optimizing processing and analysis of large and complex images by dividing them into quadrants.

- **Run-Length Coding (RLC)**: Applies run-length coding via a linked list to compress image data, encoding sequences of similar pixels to reduce storage and transmission requirements without information loss.

## Project Outcome
The project covers basic to advanced image processing tasks, leveraging hashmaps and quad trees for optimized analysis and processing. It demonstrates a robust and efficient system for handling detailed and large-scale image data, providing sophisticated tools for image analysis and manipulation in C++.

## License
This project is licensed under the [MIT License](https://opensource.org/license/MIT)- see the LICENSE file for details.

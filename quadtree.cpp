
#include "quadtree.h"

//creates a qt_node
qt::qt()
{
   // qt_node* quadNode = new qt_node;
    quadNode->flag = false; //change this?
    quadNode->r_min = NULL;
    quadNode->r_max = NULL;
    quadNode->c_min = NULL;
    quadNode->r_max = NULL;
    quadNode->deviation = NULL;
    quadNode->NW = NULL;
    quadNode->NE = NULL;
    quadNode->SW = NULL;
    quadNode->SE = NULL;
    quadNode->pixel_value = NULL;
}
qt_node* init_node() {
    qt_node* quadNode = new qt_node;
    quadNode->flag = false; //change this?
    quadNode->r_min = NULL;
    quadNode->r_max = NULL;
    quadNode->c_min = NULL;
    quadNode->r_max = NULL;
    quadNode->deviation = NULL;
    quadNode->NW = NULL;
    quadNode->NE = NULL;
    quadNode->SW = NULL;
    quadNode->SE = NULL;
    quadNode->pixel_value = NULL;
    return quadNode;
}

//adds pixel values, r_min/max, c_min/max
void add_values(qt_node* q, int* p, int num_rows, int num_cols) {
    q->p = p;
    q->prows = num_rows;
    q->pcols = num_cols;
    q->r_min = 0;
    q->r_max = num_rows - 1;
    q->c_min = 0;
    q->c_max = num_cols - 1;
}


//splits a qt_node into 4 smaller nodes with corresponding pixel values
void split_qt_node(qt_node* q) {

    int qRMin = q->r_min;
    int qRMax = q->r_max;
    int qCMin = q->c_min;
    int qCMax = q->c_max;

    bool noSouth = (qRMin == qRMax);
    bool noEast = (qCMin == qCMax);

    q->NW = init_node();
    q->NW->p = q->p;
    q->NW->prows = q->prows;
    q->NW->pcols = q->pcols;
    q->NW->r_min = qRMin;
    q->NW->r_max = (qRMax + qRMin) / 2;
    q->NW->c_min = qCMin;
    q->NW->c_max = (qCMax + qCMin) / 2;

    if (!noEast) {
        q->NE = init_node();
        q->NE->p = q->p;
        q->NE->prows = q->prows;
        q->NE->pcols = q->pcols;
        q->NE->r_min = qRMin;
        q->NE->r_max = (qRMax + qRMin) / 2;
        q->NE->c_min = (qCMax + qCMin) / 2 + 1;
        q->NE->c_max = qCMax;
    }


    if (!noSouth) {
        q->SW = init_node();
        q->SW->p = q->p;
        q->SW->prows = q->prows;
        q->SW->pcols = q->pcols;
        q->SW->r_min = (qRMax + qRMin) / 2 + 1;
        q->SW->r_max = qRMax;
        q->SW->c_min = qCMin;
        q->SW->c_max = (qCMax + qCMin) / 2;
    }

    if (!noEast && !noSouth) {
        q->SE = init_node();
        q->SE->p = q->p;
        q->SE->prows = q->prows;
        q->SE->pcols = q->pcols;
        q->SE->r_min = (qRMax + qRMin) / 2 + 1;
        q->SE->r_max = qRMax;
        q->SE->c_min = (qCMax + qCMin) / 2 + 1;
        q->SE->c_max = qCMax;
    }


}


float get_avg_pxvalue(qt_node* q) {
    float total = 0;
    int r_min = q->r_min;
    int r_max = q->r_max;
    int c_max = q->c_max;
    int c_min = q->c_min;
    int total_cells = (r_max - r_min + 1) * (c_max - c_min + 1);
    int pcols = q->pcols;
    for (int r = r_min; r <= r_max; r++) {
        for (int c = c_min; c <= c_max; c++) {
            total += q->p[r * pcols + c];
        }
    }
    float average = float(total) / float(total_cells);
    return average;
}


float get_pixel_variance(qt_node* q) {
    float average = get_avg_pxvalue(q);

    float total_dev = 0;
    int r_min = q->r_min;
    int r_max = q->r_max;
    int c_max = q->c_max;
    int c_min = q->c_min;
    int total_cells = (r_max - r_min + 1) * (c_max - c_min + 1);
    int pcols = q->pcols;
    for (int r = r_min; r <= r_max; r++) {
        for (int c = c_min; c <= c_max; c++) {
            total_dev += (average - q->p[r * pcols + c]) * (average - q->p[r * pcols + c]);
        }
    }
    float dev = total_dev / total_cells;
    return dev;
}

//builds the quad-tree based on the specified maximum pixel value variance
//splits starting node and successive nodes into child nodes
void build_tree(qt_node* start, int max_var) {
    if (start == NULL) { //NEW
        return;
    }
    float var = get_pixel_variance(start);


    if (var > max_var) {
        split_qt_node(start);
        build_tree(start->NW, max_var);
        build_tree(start->NE, max_var);
        build_tree(start->SW, max_var);
        build_tree(start->SE, max_var);
    }
    else {
        float avg = get_avg_pxvalue(start);
        start->pixel_value = avg;
        start->flag = true;
    }
}


//Unpacks the tree data into an array
//Not used in this implementation
void unpack_tree(qt_node* start, int* unpacked, int total_rows, int total_cols) {

    if (start == NULL) { //NEW
        return;
    }

    //base case
    if (start->flag) {
        int r_min = start->r_min;
        int r_max = start->r_max;
        int c_min = start->c_min;
        int c_max = start->c_max;
        int pixel_value = start->pixel_value;
        for (int r = r_min; r <= r_max; r++) {
            for (int c = c_min; c <= c_max; c++) {
                unpacked[r * total_cols + c] = pixel_value;
            }
        }
    }
    else {
        unpack_tree(start->NW, unpacked, total_rows, total_cols);
        unpack_tree(start->NE, unpacked, total_rows, total_cols);
        unpack_tree(start->SW, unpacked, total_rows, total_cols);
        unpack_tree(start->SE, unpacked, total_rows, total_cols);
    }
}



//counts leaf nodes of an already built tree
//can be a proxy for the number of pixel representations
int count_tree_nodes(qt_node* start) {
    if (start == NULL) {
        return 0;
    }
    if (start->flag) {
        return 1;
    }
    else {
        return count_tree_nodes(start->NW) + count_tree_nodes(start->NE) + count_tree_nodes(start->SW) + count_tree_nodes(start->SE);
    }
}


//Counts the number of pixels used
//Just for checking, should be equal to the image's rows * cols
int check_num_pixels(qt_node* start) {
    if (start == NULL) {
        return 0;
    }
    if (start->flag) {
        int size = (start->r_max - start->r_min + 1) * (start->c_max - start->c_min + 1);
        return size;
    }
    else {
        return check_num_pixels(start->NW) + check_num_pixels(start->NE) + check_num_pixels(start->SW) + check_num_pixels(start->SE);
    }
}
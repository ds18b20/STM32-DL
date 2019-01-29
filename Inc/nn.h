#ifndef _nn_H
#define _nn_H
/******************************************************************************
private define
define network structure
*******************************************************************************/
/* input feature params */
#define CONV1_INPUT_CHN_SIZE    1
#define CONV1_INPUT_ROW_SIZE    28
#define CONV1_INPUT_COL_SIZE    28

/* conv1 layer params */
#define CONV1_FILTER_NUM        6
#define CONV1_FILTER_CHN_SIZE   CONV1_INPUT_CHN_SIZE
#define CONV1_FILTER_SIZE       5
#define CONV1_PADDING_SIZE      0
#define CONV1_STRIDE_SIZE       1
#define CONV1_OUTPUT_CHN_SIZE   CONV1_FILTER_NUM
#define CONV1_OUTPUT_ROW_SIZE   (1+(CONV1_INPUT_ROW_SIZE+2*CONV1_PADDING_SIZE-CONV1_FILTER_SIZE)/CONV1_STRIDE_SIZE)
#define CONV1_OUTPUT_COL_SIZE   (1+(CONV1_INPUT_COL_SIZE+2*CONV1_PADDING_SIZE-CONV1_FILTER_SIZE)/CONV1_STRIDE_SIZE)

/* relu1 layer params */

/* pooling1 layer params */
#define POOLING1_WINDOW_SIZE        2
#define POOLING1_STRIDE_SIZE        2
#define POOLING1_OUTPUT_CHN_SIZE    CONV1_OUTPUT_CHN_SIZE
#define POOLING1_OUTPUT_ROW_SIZE    (CONV1_OUTPUT_ROW_SIZE/POOLING1_WINDOW_SIZE)
#define POOLING1_OUTPUT_COL_SIZE    (CONV1_OUTPUT_COL_SIZE/POOLING1_WINDOW_SIZE)

/**/
/* conv2 layer params */
#define CONV2_FILTER_NUM        8
#define CONV2_FILTER_CHN_SIZE   POOLING1_OUTPUT_CHN_SIZE
#define CONV2_FILTER_SIZE       5
#define CONV2_PADDING_SIZE      0
#define CONV2_STRIDE_SIZE       1
#define CONV2_OUTPUT_CHN_SIZE   CONV2_FILTER_NUM
#define CONV2_OUTPUT_ROW_SIZE   (1+(POOLING1_OUTPUT_ROW_SIZE+2*CONV2_PADDING_SIZE-CONV2_FILTER_SIZE)/CONV2_STRIDE_SIZE)
#define CONV2_OUTPUT_COL_SIZE   (1+(POOLING1_OUTPUT_COL_SIZE+2*CONV2_PADDING_SIZE-CONV2_FILTER_SIZE)/CONV2_STRIDE_SIZE)

/* relu2 layer params */

/* pooling2 layer params */
#define POOLING2_WINDOW_SIZE        2
#define POOLING2_STRIDE_SIZE        2
#define POOLING2_OUTPUT_CHN_SIZE    CONV2_OUTPUT_CHN_SIZE
#define POOLING2_OUTPUT_ROW_SIZE    (CONV2_OUTPUT_ROW_SIZE/POOLING2_WINDOW_SIZE)
#define POOLING2_OUTPUT_COL_SIZE    (CONV2_OUTPUT_COL_SIZE/POOLING2_WINDOW_SIZE)
/**/

// Affine1 layer
#define AFFINE1_OUTPUT_SIZE  10
#define AFFINE1_WEIGHT_NUM   AFFINE1_OUTPUT_SIZE
#define AFFINE1_WEIGHT_SIZE  (POOLING2_OUTPUT_CHN_SIZE*POOLING2_OUTPUT_ROW_SIZE*POOLING2_OUTPUT_COL_SIZE)

// Affine2 layer
#define AFFINE2_OUTPUT_SIZE  84
#define AFFINE2_WEIGHT_NUM   AFFINE2_OUTPUT_SIZE
#define AFFINE2_WEIGHT_SIZE  (AFFINE1_OUTPUT_SIZE)

// output layer
#define AFFINE3_OUTPUT_SIZE  10
#define AFFINE3_WEIGHT_NUM   AFFINE3_OUTPUT_SIZE
#define AFFINE3_WEIGHT_SIZE  AFFINE2_OUTPUT_SIZE

/******************************************************************************
private typedef
typedef data & layer
*******************************************************************************/
/* typedef Feature */
typedef struct
{
    char name[30];
    unsigned int chn_size;       /*!< channel size of Feature */
    unsigned int row_size;       /*!< row size of Feature */
    unsigned int col_size;       /*!< column size of Feature */
    float *pArray;               /*!< pointer to Feature Array */
}Feature_TypeDef;

/* Conv_Layer */
typedef struct
{
    Feature_TypeDef input_f;     /*!< conv input Feature */
    Feature_TypeDef sub_input_f; /*!< subset of conv input Feature(for conv) */
    Feature_TypeDef bias_f;      /*!< bias of conv input Feature(for conv) */
    Feature_TypeDef *pFilters;   /*!< pointer to conv filters array */
    unsigned int padding_size;   /*!< conv padding size */
    unsigned int stride_size;    /*!< conv stride size */
    Feature_TypeDef output_f;    /*!< conv output Feature */
}Conv_Layer_TypeDef;

/* Relu_Layer */
typedef struct
{
    Feature_TypeDef input_f;     /*!< input Feature */
    Feature_TypeDef output_f;    /*!< output Feature */
}Relu_Layer_TypeDef;

/* Pooling_Layer */
typedef struct
{
    Feature_TypeDef input_f;      /*!< input Feature */
    Feature_TypeDef sub_input_f;  /*!< input Feature */
    unsigned int window_size;     /*!< pooling size */
    unsigned int stride_size;     /*!< pooling size */
    Feature_TypeDef output_f;     /*!< output Feature */
}Pooling_Layer_TypeDef;

/* Affine_Layer */
typedef struct
{
    Feature_TypeDef input_f;      /*!< input Feature */
    Feature_TypeDef bias_f;       /*!< bias of affine */
    Feature_TypeDef *pWeights;    /*!< weight Features */
    unsigned int input_size;      /*!< input size */
    unsigned int output_size;     /*!< output size */
    Feature_TypeDef output_f;     /*!< output Feature */
}Affine_Layer_TypeDef;

/******************************************************************************
private functions
*******************************************************************************/
void Slice(Feature_TypeDef Src, Feature_TypeDef Dst, unsigned int start_row, unsigned int start_col);
void Slice_Single_Chn(Feature_TypeDef Src, Feature_TypeDef Dst, unsigned int slice_chn, unsigned int start_row, unsigned int start_col);
float Dot(Feature_TypeDef A, Feature_TypeDef B);
float Average(Feature_TypeDef f);
void Softmax(Feature_TypeDef f);
unsigned int Argmax(Feature_TypeDef f);
unsigned int Argmax(Feature_TypeDef f);
Feature_TypeDef Generate_Feature(char *name, unsigned int channel_size, unsigned int row_size, unsigned int column_size);
void Release_Memory(Feature_TypeDef *pFeature);  // must use pointer to modify values inside a struct to make modification effective!
void Print_Feature(Feature_TypeDef print_f);
void Run_Conv(Conv_Layer_TypeDef conv_layer);
void Run_Relu(Relu_Layer_TypeDef relu_layer);
void Run_Pooling(Pooling_Layer_TypeDef pooling_layer);
void Run_Affine(Affine_Layer_TypeDef affine_layer);
void Simple_Feature_Init(Feature_TypeDef f);
int demo(void);

#endif

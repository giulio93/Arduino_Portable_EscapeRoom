void mergeMatrix(const uint32_t *leftN, const uint32_t *rightN,uint32_t *frame){


  frame[0] = leftN[0] | rightN[0];
  frame[1] = leftN[1] | rightN[1];
  frame[2] = leftN[2] | rightN[2];


}


void setNumber(uint8_t i,uint32_t* frame){

  mergeMatrix(leftMatrix[i/10], rightMatrix[i%10],frame);

}


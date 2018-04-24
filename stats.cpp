#include "stats.h"
#include <iostream>
long stats::getSum(char channel, pair<int, int> ul, pair<int, int> lr){
  // cout<<sumRed.size()<<endl;
  long sum = 0;
  switch(channel){
    case 'r':
    if(ul.first != 0 && ul.second != 0){
      sum = sumRed[lr.first] [lr.second]
      - sumRed[ul.first - 1] [lr.second]
      - sumRed[lr.first] [ul.second - 1]
      + sumRed[ul.first - 1] [ul.second - 1];
    }
    else if(ul.first == 0 && ul.second != 0){
      sum = sumRed[lr.first] [lr.second]
      - sumRed[lr.first] [ul.second-1];
    }
    else if (ul.first != 0 && ul.second == 0){
      sum = sumRed[lr.first] [lr.second]
      - sumRed[ul.first-1] [lr.second];
    }
    else {
      sum = sumRed[lr.first] [lr.second];
    }
    break;
    case 'g':
    if(ul.first != 0 && ul.second != 0){
      sum = sumGreen[lr.first] [lr.second]
      - sumGreen[ul.first - 1] [lr.second]
      - sumGreen[lr.first] [ul.second - 1]
      + sumGreen[ul.first - 1] [ul.second - 1];
    }
    else if(ul.first == 0 && ul.second != 0){
      sum = sumGreen[lr.first] [lr.second]
      - sumGreen[lr.first] [ul.second-1];
    }
    else if (ul.first != 0 && ul.second == 0){
      sum = sumGreen[lr.first] [lr.second]
      - sumGreen[ul.first-1] [lr.second];
    }
    else {
      sum = sumGreen[lr.first] [lr.second];
    }
    break;
    case 'b':
    if(ul.first != 0 && ul.second != 0){
      sum = sumBlue[lr.first] [lr.second]
      - sumBlue[ul.first - 1] [lr.second]
      - sumBlue[lr.first] [ul.second - 1]
      + sumBlue[ul.first - 1] [ul.second - 1];
    }
    else if(ul.first == 0 && ul.second != 0){
      sum = sumBlue[lr.first] [lr.second]
      - sumBlue[lr.first] [ul.second-1];
    }
    else if (ul.first != 0 && ul.second == 0){
      sum = sumBlue[lr.first] [lr.second]
      - sumBlue[ul.first-1] [lr.second];
    }
    else {
      sum = sumBlue[lr.first] [lr.second];
    }
    break;
    default: return NULL;
  }
  return sum;
}

long stats::getSumSq(char channel, pair<int, int> ul, pair<int, int> lr){
  long sum = 0;
  switch(channel){
    case 'r':
    if(ul.first != 0 && ul.second != 0){
      sum = sumsqRed[lr.first] [lr.second]
      - sumsqRed[ul.first - 1] [lr.second]
      - sumsqRed[lr.first] [ul.second - 1]
      + sumsqRed[ul.first - 1] [ul.second - 1];
    }
    else if(ul.first == 0 && ul.second != 0){
      sum = sumsqRed[lr.first] [lr.second]
      - sumsqRed[lr.first] [ul.second-1];
    }
    else if (ul.first != 0 && ul.second == 0){
      sum = sumsqRed[lr.first] [lr.second]
      - sumsqRed[ul.first-1] [lr.second];
    }
    else {
      sum = sumsqRed[lr.first] [lr.second];
    }
    break;
    case 'g':
    if(ul.first != 0 && ul.second != 0){
      sum = sumsqGreen[lr.first] [lr.second]
      - sumsqGreen[ul.first - 1] [lr.second]
      - sumsqGreen[lr.first] [ul.second - 1]
      + sumsqGreen[ul.first - 1] [ul.second - 1];
    }
    else if(ul.first == 0 && ul.second != 0){
      sum = sumsqGreen[lr.first] [lr.second]
      - sumsqGreen[lr.first] [ul.second-1];
    }
    else if (ul.first != 0 && ul.second == 0){
      sum = sumsqGreen[lr.first] [lr.second]
      - sumsqGreen[ul.first-1] [lr.second];
    }
    else {
      sum = sumsqGreen[lr.first] [lr.second];
    }
    break;
    case 'b':
    if(ul.first != 0 && ul.second != 0){
      sum = sumsqBlue[lr.first] [lr.second]
      - sumsqBlue[ul.first - 1] [lr.second]
      - sumsqBlue[lr.first] [ul.second - 1]
      + sumsqBlue[ul.first - 1] [ul.second - 1];
    }
    else if(ul.first == 0 && ul.second != 0){
      sum = sumsqBlue[lr.first] [lr.second]
      - sumsqBlue[lr.first] [ul.second-1];
    }
    else if (ul.first != 0 && ul.second == 0){
      sum = sumsqBlue[lr.first] [lr.second]
      - sumsqBlue[ul.first-1] [lr.second];
    }
    else {
      sum = sumsqBlue[lr.first] [lr.second];
    }
    break;
    default: return NULL;
  }
  return sum;
}

void stats::resizeVec(vector<vector<long>> &vec, const unsigned short x, const unsigned short y){
  vec.resize(x);
  for(auto &it: vec){
    it.resize(y);
    // cout<<it.size()<<endl;
  }
  // cout<<vec.size()<<endl;
}

stats::stats(PNG & im){

  unsigned int x = (im.PNG::width());
  unsigned int y = (im.PNG::height());

  // vector<vector<long>> sumRed(x, vector<long>(y));
  resizeVec(sumRed, x, y);
  // vector<vector<long>> sumGreen(x, vector<long>(y));
  resizeVec(sumGreen, x, y);
  // vector<vector<long>> sumBlue(x, vector<long>(y));
  resizeVec(sumBlue, x, y);
  // vector<vector<long>> sumsqRed(x, vector<long>(y));
  resizeVec(sumsqRed, x, y);
  // vector<vector<long>> sumsqGreen(x, vector<long>(y));
  resizeVec(sumsqGreen, x, y);
  // vector<vector<long>> sumsqBlue(x, vector<long>(y));
  resizeVec(sumsqBlue, x, y);

  RGBAPixel * origin = im.PNG::getPixel(0,0);

  sumRed[0][0] = origin->r;
  sumGreen[0][0] = origin->g;
  sumBlue[0][0] = origin->b;
  sumsqRed[0][0] = origin->r * origin->r;
  sumsqGreen[0][0] = origin->g * origin->g;
  sumsqBlue[0][0] = origin->b * origin->b;

  //sets top row and left most column not including origin
  for(int i = 1; i < (int) x; i++){
    RGBAPixel * currX = im.PNG::getPixel(i, 0);
    sumRed[i][0] = currX->r + sumRed[i-1][0];
    sumGreen[i][0] = currX->g + sumGreen[i-1][0];
    sumBlue[i][0] = currX->b + sumBlue[i-1][0];
    sumsqRed[i][0] = currX->r * currX->r + sumsqRed[i-1][0];
    sumsqGreen[i][0] = currX->g * currX->g + sumsqGreen[i-1][0];
    sumsqBlue[i][0] = currX->b * currX->b + sumsqBlue[i-1][0];
    // cout<<sumRed[i][0]<<endl;
  }
  for(int i = 1; i < (int) y; i++){
    RGBAPixel * currY = im.PNG::getPixel(0, i);
    sumRed[0][i] = currY->r + sumRed[0][i-1];
    sumGreen[0][i] = currY->g + sumGreen[0][i-1];
    sumBlue[0][i] = currY->b + sumBlue[0][i-1];
    sumsqRed[0][i] = currY->r * currY->r + sumsqRed[0][i-1];
    sumsqGreen[0][i] = currY->g * currY->g + sumsqGreen[0][i-1];
    sumsqBlue[0][i] = currY->b * currY->b + sumsqBlue[0][i-1];
    // cout<<sumRed[0][i]<<endl;
  }
  for(int i = 1; i < (int) x; i++){
    for(int j = 1; j < (int) y; j++){
      RGBAPixel *  curr = im.PNG::getPixel(i, j);
      sumRed[i][j] = curr->r + sumRed[i-1][j] + sumRed[i][j-1] - sumRed[i-1][j-1];
      sumGreen[i][j] = curr->g + sumGreen[i-1][j] + sumGreen[i][j-1] - sumGreen[i-1][j-1];
      sumBlue[i][j] = curr->b + sumBlue[i-1][j] + sumBlue[i][j-1] - sumBlue[i-1][j-1];
      sumsqRed[i][j] = curr->r * curr->r + sumsqRed[i-1][j] + sumsqRed[i][j-1] - sumsqRed[i-1][j-1];
      sumsqGreen[i][j] = curr->g * curr->g + sumsqGreen[i-1][j] + sumsqGreen[i][j-1] - sumsqGreen[i-1][j-1];
      sumsqBlue[i][j] = curr->b * curr->b + sumsqBlue[i-1][j] + sumsqBlue[i][j-1] - sumsqBlue[i-1][j-1];
      // cout<<sumRed[i][j]<<endl;
    }
  }
}

long stats::getScore(pair<int, int> ul, pair<int, int>lr){
  long area = rectArea(ul, lr);
  long score = getSumSq('r', ul, lr) - (getSum('r', ul, lr) * getSum('r', ul, lr) / area)
              + getSumSq('g', ul, lr) - (getSum('g', ul, lr) * getSum('g', ul, lr) / area)
              + getSumSq('b', ul, lr) - (getSum('b', ul, lr) * getSum('b', ul, lr) / area);
  return score;
}

RGBAPixel stats::getAvg(pair<int,int> ul, pair<int, int> lr){
  long area = rectArea(ul, lr);
  return RGBAPixel((int) getSum('r', ul, lr)/area,
                   (int) getSum('g', ul, lr)/area,
                   (int) getSum('b', ul, lr)/area);
}

long stats:: rectArea(pair<int, int> ul, pair<int, int> lr){
  return (lr.first - ul.first + 1) * (lr.second - ul.second  + 1);
}

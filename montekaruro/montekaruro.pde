String[] lines;
void setup(){
  size(600, 600);
  background(33,33,33);
  stroke(255);
  noFill();
  lines = loadStrings("../test.txt");
//  for(int i = 0;i < lines.length;i++){
//    String[] s = splitTokens(lines[i], ",");
//    float x = Float.parseFloat(s[0]);
//    float y = Float.parseFloat(s[1]);
//    point((x + 1) * 150, (y + 1) * 150);
//  }
  ellipse(300, 300, width, height);
  println(lines[0]);
}

int count = 0;
  float prevx = 0;
  float prevy = 0;
int start = 0;
int bulk = 1;
void draw(){
  if(start == 1){
  for(int i = 0;i < bulk;i++){
  String[] s = splitTokens(lines[count], ",");
    float x = Float.parseFloat(s[0]);
    float y = Float.parseFloat(s[1]);
    x = (x + 1) * 300;
    y = (y + 1) * 300;
    prevx = x;
    prevy = y;
    point(x, y);
    count += 1;
    }
  }
  if(count >= 600){
    bulk = 10;
  }
  if(count >= 6600){
    bulk = 100;
  }
   
}

void keyPressed(){
  if(key == 'a'){
    start = 1;
  }
  
}

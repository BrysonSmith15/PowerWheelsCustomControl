class Ramper {
public:
  Ramper();
  Ramper(float maxAccel);
  Ramper(float maxAccel, float maxDecel);
  float get(float curr);

private:
  float prev = 0;
  float maxAccel;
  float maxDecel;
};

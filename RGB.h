class RGB {
  public:
    RGB(float red, float green, float blue);                         		// constructor; initialize the color to red, green, blue

    RGB rgb_add(RGB color1, RGB color2) const;						// add color1 and color2
    RGB rgb_sub(RGB color1, RGB color2) const;						// subtract color2 from color1
    RGB rgb_mult(RGB color1, RGB color2) const;             		// multiply color1 and color2
    RGB scalar_mult(RGB color, float scalar) const ;         		// multiply color1 by k
    RGB scalar_div(RGB color, float scalar) const ;					// divide color1 by k
    void udpate_r(float red); 										// update r
    void udpate_g(float green); 									// update g
    void udpate_b(float blue); 										// update b
    float get_r(); 													// return r
    float get_g(); 													// return g
    float get_b(); 													// return b

  private:
    float r;                      									// r value, in range [0,1]
    float b;                    									// g value
    float g;                   										// b value
};
class Color {
  public:
    Color(float red, float green, float blue);                         		// constructor; initialize the color to red, green, blue
	Color();

    Color rgb_add(Color color1, Color color2) const;						// add color1 and color2
    Color rgb_sub(Color color1, Color color2) const;						// subtract color2 from color1
    Color rgb_mult(Color color1, Color color2) const;             		// multiply color1 and color2
    Color scalar_mult(Color color, float scalar) const ;         		// multiply color1 by k
    Color scalar_div(Color color, float scalar) const ;					// divide color1 by k
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
class Color {
  public:
    Color(float red, float green, float blue);                         		// constructor; initialize the color to red, green, blue
	Color();

    static Color rgb_add(Color color1, Color color2);						// add color1 and color2
    static Color rgb_sub(Color color1, Color color2);						// subtract color2 from color1
    static Color rgb_mult(Color color1, Color color2);             		// multiply color1 and color2
    static Color scalar_mult(Color color, float scalar);         		// multiply color1 by k
    static Color scalar_div(Color color, float scalar);					// divide color1 by k
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
class Material{
public:
	Material();
	Material(float kar, float kag, float kab, 
		float kdr, float kdg, float kdb, float ksr, float ksb, float ksp,
		float krr, float krg, float krb);
	float getKar();
	float getKag();
	float getKab();
	float getKdr();
	float getKdg();
	float getKdb();
	float getKsr();
	float getKsg();
	float getKsb();
	float getKsp();
	float getKrr();
	float getKrg();
	float getKrb();
private:
	float kar, kag, kab, kdr, kdg, kdb, ksr, ksb, ksp, krr, krg, krb;
};
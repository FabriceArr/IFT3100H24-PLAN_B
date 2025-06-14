//credit https://github.com/amengede

#version 400

layout( quads ) in;

out vec3 fragmentNormal;
out vec4 fragmentPosition;



void BernsteinPolynomials(out float[4] b, out float[4] db, float t) {

	b[0] = pow(1.0 - t, 3);
	b[1] = 3.0 * pow(1.0 - t, 2) * t;
	b[2] = 3.0 * (1.0 - t) * pow(t,2);
	b[3] = pow(t, 3);

	//derivatives
	db[0] = -3.0 * pow(1.0 - t, 2);
	db[1] = -6.0 * (1.0 - t) * t + 3.0 * pow(1.0 - t,2);
	db[2] = -3.0 * pow(t, 2) + 6.0 * t * (1.0 - t);
	db[3] = 3.0 * pow(t, 2);
}

void main()
{
   float u = gl_TessCoord.x;
	float v = gl_TessCoord.y;

	vec4 p00 = gl_in[0].gl_Position;
	vec4 p01 = gl_in[1].gl_Position;
	vec4 p02 = gl_in[2].gl_Position;
	vec4 p03 = gl_in[3].gl_Position;
	vec4 p10 = gl_in[4].gl_Position;
	vec4 p11 = gl_in[5].gl_Position;
	vec4 p12 = gl_in[6].gl_Position;
	vec4 p13 = gl_in[7].gl_Position;
	vec4 p20 = gl_in[8].gl_Position;
	vec4 p21 = gl_in[9].gl_Position;
	vec4 p22 = gl_in[10].gl_Position;
	vec4 p23 = gl_in[11].gl_Position;
	vec4 p30 = gl_in[12].gl_Position;
	vec4 p31 = gl_in[13].gl_Position;
	vec4 p32 = gl_in[14].gl_Position;
	vec4 p33 = gl_in[15].gl_Position;

	//bernstein polynomials for interpolating
	//in u and v directions
	float bu[4], dbu[4], bv[4], dbv[4];
	BernsteinPolynomials(bu, dbu, u);
	BernsteinPolynomials(bv, dbv, v);

	fragmentPosition = p00*bu[0]*bv[0] + p01*bu[0]*bv[1] + p02*bu[0]*bv[2] + p03*bu[0]*bv[3] + 
		p10*bu[1]*bv[0] + p11*bu[1]*bv[1] + p12*bu[1]*bv[2] + p13*bu[1]*bv[3] + 
		p20*bu[2]*bv[0] + p21*bu[2]*bv[1] + p22*bu[2]*bv[2] + p23*bu[2]*bv[3] + 
		p30*bu[3]*bv[0] + p31*bu[3]*bv[1] + p32*bu[3]*bv[2] + p33*bu[3]*bv[3];

	vec3 dPos_du = vec3(p00*dbu[0]*bv[0] + p01*dbu[0]*bv[1] + p02*dbu[0]*bv[2] + p03*dbu[0]*bv[3] + 
		p10*dbu[1]*bv[0] + p11*dbu[1]*bv[1] + p12*dbu[1]*bv[2] + p13*dbu[1]*bv[3] + 
		p20*dbu[2]*bv[0] + p21*dbu[2]*bv[1] + p22*dbu[2]*bv[2] + p23*dbu[2]*bv[3] + 
		p30*dbu[3]*bv[0] + p31*dbu[3]*bv[1] + p32*dbu[3]*bv[2] + p33*dbu[3]*bv[3]);

	vec3 dPos_dv = vec3(p00*bu[0]*dbv[0] + p01*bu[0]*dbv[1] + p02*bu[0]*dbv[2] + p03*bu[0]*dbv[3] + 
		p10*bu[1]*dbv[0] + p11*bu[1]*dbv[1] + p12*bu[1]*dbv[2] + p13*bu[1]*dbv[3] + 
		p20*bu[2]*dbv[0] + p21*bu[2]*dbv[1] + p22*bu[2]*dbv[2] + p23*bu[2]*dbv[3] + 
		p30*bu[3]*dbv[0] + p31*bu[3]*dbv[1] + p32*bu[3]*dbv[2] + p33*bu[3]*dbv[3]);

	fragmentNormal = normalize(cross(dPos_du, dPos_dv));

	gl_Position = fragmentPosition;

}

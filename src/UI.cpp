
#include "UI.h"

void UI::setup()
{
    
	holder = new Object(ofNode(), "Holder");
	changeFocus();

	interface.setup();

	//setup for translation input
	position_slider_group.x = new ofParameter<float>();
	position_slider_group.y = new ofParameter<float>();
	position_slider_group.z = new ofParameter<float>();

	interface.add(position_slider_group.x->set("xtrans", 0.f, -100.f, 100.f));
	interface.add(position_slider_group.y->set("ytrans", 0.f, -100.f, 100.f));
	interface.add(position_slider_group.z->set("ztrans", 0.f, -100.f, 100.f));

	//setup for rotation input
	rotation_slider_group.x = new ofParameter<float>();
	rotation_slider_group.y = new ofParameter<float>();
	rotation_slider_group.z = new ofParameter<float>();
	interface.add(rotation_slider_group.x->set("xrotdeg", 0.f, 0, 360.f));
	interface.add(rotation_slider_group.y->set("yrotdeg", 0.f, 0, 360.f));
	interface.add(rotation_slider_group.z->set("zrotdeg", 0.f, 0, 360.f));

	//setup for scaling input
	scale_slider_group.x = new ofParameter<float>();
	scale_slider_group.y = new ofParameter<float>();
	scale_slider_group.z = new ofParameter<float>();
	interface.add(scale_slider_group.x->set("xscale", 1.f, -100.f, 100.f));
	interface.add(scale_slider_group.y->set("yscale", 1.f, -100.f, 100.f));
	interface.add(scale_slider_group.z->set("zscale", 1.f, -100.f, 100.f));

	//setup for selected object name input
	interface.add(selected_object_name_field.setup("Nom de l'object", *holder->getName()));

    //setup for stroke width input
    interface.add(stroke_width_slider.set("Stroke Width", 1, 0, 20));

    // Setup for fill color input
    interface.add(fill_color_slider.set("Fill Color", ofColor(255), ofColor(0, 0), ofColor(255, 255)));
    interface.add(h_slider_fill.set("Hue_fill", 0, 0, 360));
    interface.add(s_slider_fill.set("Saturation_fill", 0, 0, 1));
    interface.add(v_slider_fill.set("Value_fill", 1, 0, 1));

    // Setup for stroke color input
    interface.add(stroke_color_slider.set("Stroke Color", ofColor(0), ofColor(0, 0), ofColor(255, 255)));
    interface.add(h_slider_stroke.set("Hue_stroke", 0, 0, 360));
    interface.add(s_slider_stroke.set("Saturation_stroke", 0, 0, 1));
    interface.add(v_slider_stroke.set("Value_stroke", 1, 0, 1));
	
    // Ajoutez des callbacks pour les sliders RGB
    fill_color_slider.addListener(this, &UI::fillColorRGBChanged);
    stroke_color_slider.addListener(this, &UI::strokeColorRGBChanged);

    // Ajoutez des callbacks pour les sliders HSV
    h_slider_fill.addListener(this, &UI::hueChanged_fill);
    s_slider_fill.addListener(this, &UI::saturationChanged_fill);
    v_slider_fill.addListener(this, &UI::valueChanged_fill);

    h_slider_stroke.addListener(this, &UI::hueChanged_stroke);
    s_slider_stroke.addListener(this, &UI::saturationChanged_stroke);
    v_slider_stroke.addListener(this, &UI::valueChanged_stroke);


	//stashes slider pointer into vector for output towards scene object in order to control objects inside of it
	trans_sliders_pointer.push_back(position_slider_group.x);
	trans_sliders_pointer.push_back(position_slider_group.y);
	trans_sliders_pointer.push_back(position_slider_group.z);

	rot_sliders_pointer.push_back(rotation_slider_group.x);
	rot_sliders_pointer.push_back(rotation_slider_group.y);
	rot_sliders_pointer.push_back(rotation_slider_group.z);

	scale_sliders_pointer.push_back(scale_slider_group.x);
	scale_sliders_pointer.push_back(scale_slider_group.y);
	scale_sliders_pointer.push_back(scale_slider_group.z);

}

void UI::update()
{
}

void UI::draw()
{
	interface.draw();
	
}

const vector<ofParameter<float>*> UI::getPositionSliderValues() {
	ofLog() << "In UI- " << position_slider_group.x;
	return trans_sliders_pointer;
}

const vector<ofParameter<float>*> UI::getRotationSliderValues()
{

	return rot_sliders_pointer;
}

const vector<ofParameter<float>*> UI::getScaleSliderValues()
{

	return scale_sliders_pointer;
}


const ofParameter<ofColor> UI::getFillColorSlider()
{
	return fill_color_slider;
}

const ofParameter<ofColor> UI::getStrokeColorSlider()
{
	return stroke_color_slider;
}

const ofParameter<int> UI::getStrokeWidthSlider()
{
	return stroke_width_slider;

ofVec3f* UI::setPositionSliderValues()
{
	position_slider_group.x->reInit();
	position_slider_group.y->reInit();
	position_slider_group.z->reInit();
	return nullptr;
}

ofVec3f* UI::setRotationSliderValues()
{
	rotation_slider_group.x->reInit();
	rotation_slider_group.y->reInit();
	rotation_slider_group.z->reInit();
	return nullptr;
}

ofVec3f* UI::setScaleSliderValues()
{
	scale_slider_group.x->reInit();
	scale_slider_group.y->reInit();
	scale_slider_group.z->reInit();
	return nullptr;
}


void UI::changeFocus(const Object* Obj) {
	//si la fonction demande de changer le focus vers rien, 
	//le focus est changer vers le place holder du UI
	if (Obj != nullptr) {
		selected_object = Obj;
	}
	else {
		selected_object = holder;
	}
	
}

void UI::exit()
{
	delete holder;
	delete selected_object;

	//empties all vector objects.
	for (std::vector<ofParameter<float>*>::const_iterator it =
		trans_sliders_pointer.begin(); it !=
		trans_sliders_pointer.end(); it++)
	{
		delete (*it);
	}
	
	for (std::vector<ofParameter<float>*>::const_iterator it =
		rot_sliders_pointer.begin(); it !=
		rot_sliders_pointer.end(); it++)
	{
		delete (*it);
	}
	for (std::vector<ofParameter<float>*>::const_iterator it =
		scale_sliders_pointer.begin(); it !=
		scale_sliders_pointer.end(); it++)
	{
		delete (*it);
	}

}


bool UI::addObject() {
	//affiche le selecteur de primitive
	//return true si afficher, false si deja afficher
	return false;
}

bool UI::removeObject() {
	//cache le selecteur de primitive
	//return true si cacher, false si il etait deja cacher
	return false;
}

hsv UI::rgbToHSV(ofColor color)
{
    hsv out;
    float r = color.r / 255.0;
    float g = color.g / 255.0;
    float b = color.b / 255.0;

    double min, max, delta;

    min = r < g ? r : g;
    min = min < b ? min : b;

    max = r > g ? r : g;
    max = max > b ? max : b;

    out.v = max;
    delta = max - min;

    if (delta < 0.00001)
    {
        out.s = 0;
        out.h = 0; // undefined, maybe nan?
        return out;
    }

    if (max > 0.0) {
        out.s = (delta / max);
    }
    else {
        out.s = 0.0;
        out.h = NAN;
        return out;
    }

    if (r >= max)
        out.h = (g - b) / delta;
    else if (g >= max)
        out.h = 2.0 + (b - r) / delta;
    else
        out.h = 4.0 + (r - g) / delta;

    out.h *= 60.0;

    if (out.h < 0.0)
        out.h += 360.0;

    return out;
}

ofColor UI::hsvToRGB(hsv hsvColor)
{
    double hh, p, q, t, ff;
    long i;
    rgb out;

    if (hsvColor.s <= 0.0) {
        out.r = hsvColor.v;
        out.g = hsvColor.v;
        out.b = hsvColor.v;
        return ofColor(out.r * 255, out.g * 255, out.b * 255);
    }

    hh = hsvColor.h;
    if (hh >= 360.0) hh = 0.0;
    hh /= 60.0;
    i = (long)hh;
    ff = hh - i;
    p = hsvColor.v * (1.0 - hsvColor.s);
    q = hsvColor.v * (1.0 - (hsvColor.s * ff));
    t = hsvColor.v * (1.0 - (hsvColor.s * (1.0 - ff)));

    switch (i) {
    case 0:
        out.r = hsvColor.v;
        out.g = t;
        out.b = p;
        break;
    case 1:
        out.r = q;
        out.g = hsvColor.v;
        out.b = p;
        break;
    case 2:
        out.r = p;
        out.g = hsvColor.v;
        out.b = t;
        break;

    case 3:
        out.r = p;
        out.g = q;
        out.b = hsvColor.v;
        break;
    case 4:
        out.r = t;
        out.g = p;
        out.b = hsvColor.v;
        break;
    case 5:
    default:
        out.r = hsvColor.v;
        out.g = p;
        out.b = q;
        break;
    }

    return ofColor(out.r * 255, out.g * 255, out.b * 255);
}

void UI::setHSVSlidersFromRGB(ofColor rgbColor, bool isFillColor)
{
    hsv hsvColor = rgbToHSV(rgbColor);

    if (isFillColor) {
        h_slider_fill = hsvColor.h;
        s_slider_fill = hsvColor.s;
        v_slider_fill = hsvColor.v;
    }
    else {
        h_slider_stroke = hsvColor.h;
        s_slider_stroke = hsvColor.s;
        v_slider_stroke = hsvColor.v;
    }
}

void UI::fillColorRGBChanged(ofColor& color)
{
    setHSVSlidersFromRGB(color, true);
}

void UI::strokeColorRGBChanged(ofColor& color)
{
    setHSVSlidersFromRGB(color, false);
}

void UI::hueChanged_fill(float& value)
{
    // Mettez � jour les sliders de couleur RGB en fonction des sliders de couleur HSV
    ofColor rgbColor_fill = hsvToRGB({ h_slider_fill, s_slider_fill, v_slider_fill });
    fill_color_slider = rgbColor_fill;
}

void UI::saturationChanged_fill(float& value)
{
    // Mettez � jour les sliders de couleur RGB en fonction des sliders de couleur HSV
    ofColor rgbColor_fill = hsvToRGB({ h_slider_fill, s_slider_fill, v_slider_fill });
    fill_color_slider = rgbColor_fill;
}

void UI::valueChanged_fill(float& value)
{
    // Mettez � jour les sliders de couleur RGB en fonction des sliders de couleur HSV
    ofColor rgbColor_fill = hsvToRGB({ h_slider_fill, s_slider_fill, v_slider_fill });
    fill_color_slider = rgbColor_fill;
}

void UI::hueChanged_stroke(float& value)
{
    // Mettez � jour les sliders de couleur RGB en fonction des sliders de couleur HSV
    ofColor rgbColor_stroke = hsvToRGB({ h_slider_stroke, s_slider_stroke, v_slider_stroke });
    stroke_color_slider = rgbColor_stroke;
}

void UI::saturationChanged_stroke(float& value)
{
    // Mettez � jour les sliders de couleur RGB en fonction des sliders de couleur HSV
    ofColor rgbColor_stroke = hsvToRGB({ h_slider_stroke, s_slider_stroke, v_slider_stroke });
    stroke_color_slider = rgbColor_stroke;
}

void UI::valueChanged_stroke(float& value)
{
    // Mettez � jour les sliders de couleur RGB en fonction des sliders de couleur HSV
    ofColor rgbColor_stroke = hsvToRGB({ h_slider_stroke, s_slider_stroke, v_slider_stroke });
    stroke_color_slider = rgbColor_stroke;
}
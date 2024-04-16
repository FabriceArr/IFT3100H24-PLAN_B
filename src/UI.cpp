
#include "UI.h"

void UI::setup()
{

	interface.setup();

    tone_mapping_exposure = 1.0f;
    tone_mapping_gamma = 2.2f;
    tone_mapping_toggle = true;
    illuminationModel_selection = illum_enum::flat;

    // Setup for Background color input
    interface.add(background_color_slider.set("background Color", ofColor(255), ofColor(0, 0), ofColor(255, 255)));
    interface.add(h_slider_background.set("Hue_background", 0, 0, 360));
    interface.add(s_slider_background.set("Saturation_background", 0, 0, 1));
    interface.add(v_slider_background.set("Value_background", 1, 0, 1));

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
	interface.add(scale_slider_group.x->set("xscale", 1.f, -9.f, 10.f));
	interface.add(scale_slider_group.y->set("yscale", 1.f, -9.f, 10.f));
	interface.add(scale_slider_group.z->set("zscale", 1.f, -9.f, 10.f));

	//setup for selected object name input
	//interface.add(selected_object_name_field.setup("Nom de l'object", *holder->getName()));

    //setup for stroke width input
    interface.add(stroke_width_slider.set("Stroke Width", 1, 0, 20));

    // Setup for fill color input
    interface.add(fill_color_slider.set("Fill Color", ofColor(255), ofColor(0, 0), ofColor(255, 255)));
    interface.add(h_slider_fill.set("Hue_fill", 0, 0, 360));
    interface.add(s_slider_fill.set("Saturation_fill", 0, 0, 1));
    interface.add(v_slider_fill.set("Value_fill", 1, 0, 1));

    // Setup for Illumination Model dropdown
    interface.add(IlluminationModel_dropdown.setup("Modele d'Illumination"));
    IlluminationModel_dropdown.add(illuminationModel_vector);
    IlluminationModel_dropdown.disableMultipleSelection();
    IlluminationModel_dropdown.enableCollapseOnSelection();
    IlluminationModel_dropdown.setSelectedValueByIndex(0, true);
    //IlluminationModel_dropdown.addListener(this, &UI::onIllumModelChangeStr);

    // Setup for Image filter dropdown
    interface.add(imageFilter_dropdown.setup("Filtrage de Texture"));
    imageFilter_dropdown.add(filter_vector);
    imageFilter_dropdown.disableMultipleSelection();
    imageFilter_dropdown.enableCollapseOnSelection();
    imageFilter_dropdown.setSelectedValueByIndex(0, true);
    //imageFilter_dropdown.addListener(this, &UI::onFilterChangeStr);

    // Setup for stroke color input
    interface.add(stroke_color_slider.set("Stroke Color", ofColor(0), ofColor(0, 0), ofColor(255, 255)));
    interface.add(h_slider_stroke.set("Hue_stroke", 0, 0, 360));
    interface.add(s_slider_stroke.set("Saturation_stroke", 0, 0, 1));
    interface.add(v_slider_stroke.set("Value_stroke", 1, 0, 1));

    group_point.setup("Primitive Vector Points");

    // Setup for three points
    group_point.add(intInputPoint1X.setup("Point 1 : x =", 0));
    group_point.add(intInputPoint1Y.setup("Point 1 : y =", 0));
    group_point.add(intInputPoint2X.setup("Point 2 : x =", 0));
    group_point.add(intInputPoint2Y.setup("Point 2 : y =", 0));
    group_point.add(intInputPoint3X.setup("Point 3 : x =", 0));
    group_point.add(intInputPoint3Y.setup("Point 3 : y =", 0));

    // Setup for radius
    group_point.add(intInputRadiusX.setup("radius : x =", 3));
    group_point.add(intInputRadiusY.setup("radius : y =", 3));

    interface.add(&group_point);
	
    // Ajoutez des callbacks pour les sliders RGB
    background_color_slider.addListener(this, &UI::backgroundColorRGBChanged);
    fill_color_slider.addListener(this, &UI::fillColorRGBChanged);
    stroke_color_slider.addListener(this, &UI::strokeColorRGBChanged);

    // Ajoutez des callbacks pour les sliders HSV
    h_slider_background.addListener(this, &UI::hueChanged_background);
    s_slider_background.addListener(this, &UI::saturationChanged_background);
    v_slider_background.addListener(this, &UI::valueChanged_background);

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

    slider_exposure.set("exposure", tone_mapping_exposure, 0.0f, 5.0f);
    slider_gamma.set("gamma", tone_mapping_gamma, 0.0f, 5.0f);

    group_tone_mapping.setup("tone mapping");

    group_tone_mapping.add(slider_exposure);
    group_tone_mapping.add(slider_gamma);
    group_tone_mapping.add(toggle_tone_mapping);

    slider_diffuse_color.set("diffuse color", ofColor(255), ofColor(0, 0), ofColor(255, 255));
    slider_specular_color.set("specular color", ofColor(255), ofColor(0, 0), ofColor(255, 255));
    slider_emissive_color.set("emissive color", ofColor(255), ofColor(0, 0), ofColor(255, 255));
    slider_ambiant_color.set("ambiant color", ofColor(255), ofColor(0, 0), ofColor(255, 255)); 
    slider_shininess.set("shininess", material_shininess, 0.0f, 40.0f);

    group_material.setup("material");

    group_material.add(slider_ambiant_color);
    group_material.add(slider_diffuse_color);
    group_material.add(slider_emissive_color);
    group_material.add(slider_specular_color);
    group_material.add(slider_shininess);

    interface.add(&group_tone_mapping);
    interface.add(&group_material);
}

void UI::update()
{
    tone_mapping_exposure = slider_exposure;
    tone_mapping_gamma = slider_gamma;
    tone_mapping_toggle = toggle_tone_mapping;
    illuminationModel_selection = static_cast<illum_enum>(illumination_model.get());
    //IlluminationModel_dropdown.getAllSelected()[0]
}

void UI::draw()
{
    if (tone_mapping_toggle)
        toggle_tone_mapping.set("aces filmic", true);
    else
        toggle_tone_mapping.set("reinhard", false);

    /*
    string temp = IlluminationModel_dropdown.getAllSelected()[0];
    //ofLog() << "Illum model : " << temp;
    if (temp == "flat")
        illumination_model.set(flat);
    else if (temp == "lambert")
        illumination_model.set(lambert);
    else if (temp == "gouraud")
        illumination_model.set(gouraud);
    else if (temp == "phong")
        illumination_model.set(phong);
    else if (temp == "blinnPhong")
        illumination_model.set(blinnPhong);
        */
	interface.draw();
}

const ofVec3f UI::getPoint1Values()
{
    point1_values.x = intInputPoint1X;
    point1_values.y = intInputPoint1Y;
    return point1_values;
}

const ofVec3f UI::getPoint2Values()
{
    point2_values.x = intInputPoint2X;
    point2_values.y = intInputPoint2Y;
    return point2_values;
}

const ofVec3f UI::getPoint3Values()
{
    point3_values.x = intInputPoint3X;
    point3_values.y = intInputPoint3Y;
    return point3_values;
}

const ofVec3f UI::getRadiusValues()
{
    radius_values.x = intInputRadiusX;
    radius_values.y = intInputRadiusY;
    return radius_values;
}

const vector<ofParameter<float>*> UI::getPositionSliderValues() {
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

const ofParameter<ofColor> UI::getBackgroundColorSlider()
{
	return background_color_slider;
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
}

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

float* UI::setExposureSlider()
{
	slider_exposure.reInit();
	return nullptr;
}

float* UI::setGammaSlider()
{
	slider_gamma.reInit();
	return nullptr;
}

bool* UI::setToneMappingToggle()
{
	toggle_tone_mapping.reInit();
	return nullptr;
}

illum_enum* UI::setIllumModel()
{
    //illumination_model.set(static_cast<int>(illuminationModel_selection));
    illumination_model.reInit();
    return nullptr;
}

ofParameter<float>* UI::getExposureSlider()
{
	return &slider_exposure;
}

ofParameter<float>* UI::getGammaSlider()
{
	return &slider_gamma;
}

ofParameter<bool>* UI::getToneMappingToggle()
{
	return &toggle_tone_mapping;
}

ofParameter<int>* UI::getIllumModel()
{
    return &illumination_model;
}
ofParameter<ofColor>* UI::getAmbiantColor()
{
	return &slider_ambiant_color;
}

ofParameter<ofColor>* UI::getDiffuseColor()
{
	return &slider_diffuse_color;
}

ofParameter<ofColor>* UI::getEmissiveColor()
{
	return &slider_emissive_color;
}

ofParameter<ofColor>* UI::getSpecularColor()
{
	return &slider_specular_color;
}

ofParameter<float>* UI::getShininess()
{
	return &slider_shininess;
}

ofColor* UI::setAmbiantColor()
{
	slider_ambiant_color.reInit();
    return nullptr;
}

ofColor* UI::setDiffuseColor()
{
	slider_diffuse_color.reInit();
	return nullptr;
}

ofColor* UI::setEmissiveColor()
{
	slider_emissive_color.reInit();
	return nullptr;
}

ofColor* UI::setSpecularColor()
{
	slider_specular_color.reInit();
    return nullptr;
}

float* UI::setShininess()
{
	slider_shininess.reInit();
    return nullptr;
}

void UI::changeFocus(const Object* Obj) {
	//si la fonction demande de changer le focus vers rien, 
	//le focus est changer vers le place holder du UI
	if (Obj != nullptr) {
		selected_object = Obj;
	}
	else {
        selected_object = nullptr;
	}
}

void UI::exit()
{
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

void UI::backgroundColorRGBChanged(ofColor& color)
{
	setHSVSlidersFromRGB(color, false);
}

void UI::hueChanged_background(float& value)
{
	// Mettez � jour les sliders de couleur RGB en fonction des sliders de couleur HSV
	ofColor rgbColor_background = hsvToRGB({ h_slider_background, s_slider_background, v_slider_background });
	background_color_slider = rgbColor_background;
}

void UI::saturationChanged_background(float& value)
{
	// Mettez � jour les sliders de couleur RGB en fonction des sliders de couleur HSV
	ofColor rgbColor_background = hsvToRGB({ h_slider_background, s_slider_background, v_slider_background });
	background_color_slider = rgbColor_background;
}

void UI::valueChanged_background(float& value)
{
	// Mettez � jour les sliders de couleur RGB en fonction des sliders de couleur HSV
	ofColor rgbColor_background = hsvToRGB({ h_slider_background, s_slider_background, v_slider_background });
	background_color_slider = rgbColor_background;
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
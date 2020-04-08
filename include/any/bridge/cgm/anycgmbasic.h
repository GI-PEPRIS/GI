#ifndef _ANYBRIDGE_CGMBASIC_H_
#define _ANYBRIDGE_CGMBASIC_H_

// Refer to EXPORT & IMPORT
#include "..\anybridge.h"

namespace AnyBridge
{
	/*!
	*	分界符, Class-0
	**/
	enum Delimiter
	{
		Delimiter_No_Op =0,
		Delimiter_Begin_Metafile = 1,
		Delimiter_End_Metafile = 2,
		Delimiter_Begin_Picture =3,
		Delimiter_Begin_Picture_Body = 4,
		Delimiter_End_Picture =5,
		Delimiter_Begin_Segment =6,
		Delimiter_End_Segment =7,
		Delimiter_Begin_Figure =8,
		Delimiter_End_Figure =9,
		Delimiter_Begin_Protection_Region =13,
		Delimiter_End_Protection_Region =14,
		Delimiter_Begin_Compound_Line =15,
		Delimiter_End_Compound_Line =16,
		Delimiter_Begin_Compound_Text_Path =17,
		Delimiter_End_Compound_Text_Path =18,
		Delimiter_Begin_Tile_Array =19,
		Delimiter_End_Tile_Array =20,
		Delimiter_Begin_Application_Structure =21,
		Delimiter_Begin_Application_Structure_Body =22,
		Delimiter_End_Application_Structure =23
	};

	/*!
	*	元文件描述符, Class-1
	**/
	enum MetafileDiscription
	{
		MetafileDiscription_Metafile_Version =1,
		MetafileDiscription_Metafile_Description =2,
		MetafileDiscription_Vdc_Type =3,
		MetafileDiscription_Integer_Precision =4,
		MetafileDiscription_Real_Precision =5,
		MetafileDiscription_Index_Precision =6,
		MetafileDiscription_Colour_Precision =7,
		MetafileDiscription_Colour_Index_Precision =8,
		MetafileDiscription_Maximum_Colour_Index =9,
		MetafileDiscription_Colour_Value_Extent =10,
		MetafileDiscription_Metafile_Element_List =11,
		MetafileDiscription_Metafile_Defaults_Replacement =12,
		MetafileDiscription_Font_List =13, 
		MetafileDiscription_Character_Set_List =14,
		MetafileDiscription_Character_Coding_Announcer =15,
		MetafileDiscription_Name_Precision =16,
		MetafileDiscription_Maximum_Vdc_Extent =17,
		MetafileDiscription_Segment_Priority_Extent =18,
		MetafileDiscription_Colour_Model =19,
		MetafileDiscription_Colour_Calibration =20,
		MetafileDiscription_Font_Properties =21,
		MetafileDiscription_Glyph_Mapping =22,
		MetafileDiscription_Symbol_Library_List =23,
		MetafileDiscription_Picture_Directory =24
	};

	/*!
	*	图片描述符元素, Class-2
	**/
	enum PictureDiscription
	{
		PictureDiscription_Scaling_Mode =1,
		PictureDiscription_Colour_Selection_Mode =2,
		PictureDiscription_Line_Width_Specification_Mode =3,
		PictureDiscription_Marker_Size_Specification_Mode =4,
		PictureDiscription_Edge_Width_Specification_Mode =5,
		PictureDiscription_Vdc_Extent =6,
		PictureDiscription_Background_Colour =7,
		PictureDiscription_Device_Viewport =8,
		PictureDiscription_Device_Viewport_Specification_Mode =9,
		PictureDiscription_Device_Viewport_Mapping =10,
		PictureDiscription_Line_Representation =11,
		PictureDiscription_Marker_Representation =12,
		PictureDiscription_Text_Representation =13,
		PictureDiscription_Fill_Representation =14,
		PictureDiscription_Edge_Representation =15,
		PictureDiscription_Interior_Style_Specification_Mode =16,
		PictureDiscription_Line_And_Edge_Type_Definition =17,
		PictureDiscription_Hatch_Style_Definition =18,
		PictureDiscription_Geometric_Pattern_Definition =19,
		PictureDiscription_Application_Structure_Directory =20
	};

	/*!
	*	控制元素, Class-3
	**/
	enum ControlElements
	{
		ControlElements_Vdc_Integer_Precision =1,
		ControlElements_Vdc_Real_Precision =2,
		ControlElements_Auxiliary_Colour =3,
		ControlElements_Transparency =4,
		ControlElements_Clip_Rectangle =5,
		ControlElements_Clip_Indicator =6,
		ControlElements_Line_Clipping_Mode =7,
		ControlElements_Marker_Clipping_Mode =8,
		ControlElements_Edge_Clipping_Mode =9,
		ControlElements_New_Region =10,
		ControlElements_Save_Primitive_Context =11,
		ControlElements_Restore_Primitive_Context =12,
		ControlElements_Protection_Region_Indicator =17,
		ControlElements_Generalized_Text_Path_Mode =18,
		ControlElements_Mitre_Limit =19,
		ControlElements_Transparent_Cell_Colour =20
	};

	/*!
	*	图元, Class-4 
	**/
	enum GraphicPrimitives
	{
		GraphicPrimitives_Polyline =1,
		GraphicPrimitives_Disjoint_Polyline =2,
		GraphicPrimitives_Polymarker =3,
		GraphicPrimitives_Text =4,
		GraphicPrimitives_Restricted_Text =5,
		GraphicPrimitives_Append_Text =6,
		GraphicPrimitives_Polygon =7,
		GraphicPrimitives_Polygon_Set =8,
		GraphicPrimitives_Cell_Array =9,
		GraphicPrimitives_Generalized_Drawing_Primitive =10,
		GraphicPrimitives_Rectangle =11,
		GraphicPrimitives_Circle =12,
		GraphicPrimitives_Circular_Arc_Point =13,
		GraphicPrimitives_Circular_Arc_Point_Close =14,
		GraphicPrimitives_Circular_Arc_Centre =15,
		GraphicPrimitives_Circular_Arc_Centre_Close =16,
		GraphicPrimitives_Ellipse =17,
		GraphicPrimitives_Elliptical_Arc =18,
		GraphicPrimitives_Elliptical_Arc_Close =19,
		GraphicPrimitives_Circular_Arc_Centre_Reversed =20,
		GraphicPrimitives_Connecting_Edge =21,
		GraphicPrimitives_Hyperbolic_Arc =22,
		GraphicPrimitives_Parabolic_Arc =23,
		GraphicPrimitives_Non_Uniform_B_Spline =24,
		GraphicPrimitives_Non_Uniform_Rational_B_Spline =25,
		GraphicPrimitives_Polybezier =26,
		GraphicPrimitives_Polysymbol =27,
		GraphicPrimitives_Bitonal_Tile =28,
		GraphicPrimitives_Tile =29
	};

	/*!
	*	属性, Class-5
	**/
	enum AttributeElements
	{
		//////////////////////////
		// 线束序号
		AttributeElements_Line_Bundle_Index =1,
		// 线型
		AttributeElements_Line_Type =2,
		// 线宽
		AttributeElements_Line_Width =3,
		// 线颜色
		AttributeElements_Line_Colour =4,
		//////////////////////////
		// 标记束序号
		AttributeElements_Marker_Bundle_Index =5, 
		// 标记类型
		AttributeElements_Marker_Type =6,
		// 标记大小
		AttributeElements_Marker_Size =7,
		// 标记颜色
		AttributeElements_Marker_Colour =8,
		//////////////////////////
		// 文本束序号
		AttributeElements_Text_Bundle_Index =9,
		// 文本字体序号
		AttributeElements_Text_Font_Index =10,
		// 文本精度
		AttributeElements_Text_Precision =11,
		// 文本缩放系数
		AttributeElements_Character_Expansion_Factor =12,
		// 文本间距
		AttributeElements_Character_Spacing =13,
		// 文本颜色
		AttributeElements_Text_Colour =14,
		// 文本高度
		AttributeElements_Character_Height =15,
		// 文本方向
		AttributeElements_Character_Orientation =16,
		// 文本路径
		AttributeElements_Text_Path =17,
		// 文本排列方式
		AttributeElements_Text_Alignment =18,
		// 字符集序号
		AttributeElements_Character_Set_Index =19,
		// 候选字符集序号
		AttributeElements_Alternate_Character_Set_Index =20,
		// 填充束序号
		AttributeElements_Fill_Bundle_Index =21,
		// 内部风格
		AttributeElements_Interior_Style =22,
		// 填充色
		AttributeElements_Fill_Colour =23,
		// 
		AttributeElements_Hatch_Index =24,
		// 样式索引
		AttributeElements_Pattern_Index =25,
		// 边束序号
		AttributeElements_Edge_Bundle_Index =26,
		// 边类型
		AttributeElements_Edge_Type =27,
		// 边宽
		AttributeElements_Edge_Width =28,
		// 边颜色
		AttributeElements_Edge_Colour =29,
		// 边可见性
		AttributeElements_Edge_Visibility =30,
		AttributeElements_Fill_Reference_Point =31,
		AttributeElements_Pattern_Table =32,
		AttributeElements_Pattern_Size =33,
		AttributeElements_Colour_Table =34,
		AttributeElements_Aspect_Source_Flags =35,
		AttributeElements_Pick_Identifier =36,
		AttributeElements_Line_Cap =37,
		AttributeElements_Line_Join =38,
		AttributeElements_Line_Type_Continuation =39,
		AttributeElements_Line_Type_Initial_Offset =40,
		AttributeElements_Text_Score_Type =41,
		AttributeElements_Restricted_Text_Type  =42,
		AttributeElements_Interpolated_Interior  =43,
		AttributeElements_Edge_Cap  =44,
		AttributeElements_Edge_Join  =45,
		AttributeElements_Edge_Type_Continuation  =46,
		AttributeElements_Edge_Type_Initial_Offset  =47,
		AttributeElements_Symbol_Library_Index  =48,
		AttributeElements_Symbol_Colour =49,
		AttributeElements_Symbol_Size =50,
		AttributeElements_Symbol_Orientation  =51
	};

	/*!
	*	出口元素, Class-6
	**/
	enum EscapeElements
	{
		EscapeElements_Escape =1	
	};

	/*!
	*	外部元素, Class-7
	**/
	enum ExternalElements
	{
		ExternalElements_Message =1,
		ExternalElements_Application_Data =2
	};

	/*!
	*	分段元素, Class-8
	**/
	enum SegmentElements
	{
		SegmentElements_Copy_Segment =1,
		SegmentElements_Inheritance_Filter =2,
		SegmentElements_Clip_Inheritance =3,
		SegmentElements_Segment_Transformation =4,
		SegmentElements_Segment_Highlighting =5,
		SegmentElements_Segment_Display_Priority =6,
		SegmentElements_Segment_Pick_Priority =7
	};

	/*!
	*	结构应用元素, Class-9
	**/
	enum ApplicationStructureDescriptor
	{
		ApplicationStructureDescriptor_Application_Structure_Attribute =1
	};





}

#endif
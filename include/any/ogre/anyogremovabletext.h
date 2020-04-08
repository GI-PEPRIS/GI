/*!
 * The AnyOGRE of PetroCOVERY Solution is a collection of native C++ classes that implement 
 * the domain data model etc.
 *
 * Copyright (C) 2015 XIUJIE SHENG
 *
 * This library isn't a free software, so you cann't take the source code without author's permit.
 * Of course, there is NO ANY WARRANTY that this library will not harm your computer or ongoing 
 * business if you illegally got it. 
 *
 * NOTE: 
 * AUTHOR WOULD ALWAYS RESERVE LEGAL RIGHT TO PROTECT WHAT HE HAVE DONE ACCORDING TO
 * LOCAL OR INTERNATIONAL COPYRIGHT OR RELATIVE LAW(S).
 *
 * For more information, contact:
 *
 * China University of Geoseciences(Wuhan)
 * Resource Faculty
 *
 * Xiujie Sheng
 * herman.sheng@gmail.com
 */
#ifndef __ANYOGRE_OGRE_MOVEABLE_TEXT_H__
#define __ANYOGRE_OGRE_MOVEABLE_TEXT_H__

//
#include "anyogre.h"

//
#include "ogre\Ogre.h"
#include "OGRE\OgrePrerequisites.h"
#include"OGRE\Overlay\OgreFont.h"
#include "OGRE\Overlay\OgreFontManager.h"
#include "OGRE\Overlay\OgreOverlayManager.h"
#include "OGRE\Overlay\OgreOverlayContainer.h"

using namespace Ogre;

//
namespace AnyOGRE
{
	class ANYOGRE_CLASS CAnyOgreMovableText : public MovableObject, public Renderable
	{
	public:
		/// 水平对齐方式
		enum HorizontalAlignment
		{
			H_LEFT,		///< 左对齐
			H_CENTER,	///< 居中
			H_RIGHT		///< 右对齐
		};

		/// 垂直对齐方式
		enum VerticalAlignment
		{
			V_BELOW,///< 低端对齐
			V_ABOVE,///< 顶端对齐
			V_CENTER///< 居中
		};

	public:
		String				mFontName;///<
		String				mType;///<
		String				mName;///<
		DisplayString		mCaption;///< 
		HorizontalAlignment	mHorizontalAlignment;///< 水平对齐方式
		VerticalAlignment	mVerticalAlignment;///< 垂直对齐方式

		ColourValue			mColor;///<
		RenderOperation		mRenderOp;///<
		AxisAlignedBox		mAABB;///<
		LightList			mLList;///<

		Real				mCharHeight;///<
		Real				mSpaceWidth;///<

		bool				mNeedUpdate;///< 
		bool				mUpdateColors;///<
		bool				mOnTop;///<

		Real				mTimeUntilNextToggle;///<
		Real				mRadius;///< 包围半径
		Real				mAdditionalHeight;///<

		Camera*				mpCam;///< 摄像机指针
		RenderWindow*		mpWin;///< 渲染窗口指针
		Ogre::FontPtr				mpFont;///< 字体指针
		MaterialPtr			mpMaterial;///< 
		MaterialPtr			mpBackgroundMaterial;///< 背景材质

		Vector3				mPositionOffset;///< 
		Vector3				mScaleOffset;///<

	public:
		/// 构造函数
		/// @param[in] name 标识名
		/// @param[in] caption 字幕字符串
		/// @param[in] fontName 字体名
		/// @param[in] charHeight 字符高度
		/// @param[in] colour 字符颜色
		CAnyOgreMovableText(const Ogre::String& name,
			const Ogre::DisplayString& caption,
			const Ogre::String& fontName = "MyFont",
			Ogre::Real charHeight = 1.0f,
			Ogre::Real spaceWidth = 0.0f,
			const Ogre::ColourValue& colour = Ogre::ColourValue::White);

		virtual ~CAnyOgreMovableText(void);

		/// 设置字体名
		void    setFontName(const String &fontName);

		/// 设置显示字幕
		void    setCaption(const DisplayString &caption);

		/// 设置文字颜色
		void    setColor(const ColourValue &color);

		/// 设置文字高度
		void    setCharacterHeight(Real height);

		/// 设置间隔宽度
		void    setSpaceWidth(Real width);

		/// 设置文字对齐方式
		void    setTextAlignment(const HorizontalAlignment& horizontalAlignment,
			const VerticalAlignment& verticalAlignment);

		/// 设置
		void    setAdditionalHeight( Real height );

		/// 是否最前方显示
		void    showOnTop(bool show=true);

		/// 
		void setPositionOffset(const Ogre::Vector3& offset);

		/// 
		Ogre::Vector3 getPositionOffset() const { return mPositionOffset; }

		/// 
		void setScaleOffset(const Ogre::Vector3& offset);

		/// 
		Ogre::Vector3 getScaleOffset() const { return mScaleOffset; }

		/// 获取字体名
		const   String&			getFontName() const {return mFontName;}

		/// 获取字幕字符串
		const   DisplayString&	getCaption() const {return mCaption;}

		/// 获取字体颜色
		const   ColourValue&	getColor() const {return mColor;}

		/// 获取字符高度
		Real    getCharacterHeight() const {return mCharHeight;}

		/// 获取间隔宽度
		Real    getSpaceWidth() const {return mSpaceWidth;}

		/// 
		Real    getAdditionalHeight() const {return mAdditionalHeight;}

		/// 获取是否在最前方显示
		bool    getShowOnTop() const {return mOnTop;}

		/// 获取包围盒
		AxisAlignedBox	        GetAABB(void) { return mAABB; }
		virtual void visitRenderables(Renderable::Visitor* visitor, bool debugRenderables = false)
		{

		};

		///
		void SetOffset(double xOffset, double yOffset)
		{
			m_xOffset = xOffset;
			m_yOffset = yOffset;
		}

	protected:
		double m_xOffset;
		double m_yOffset;
		// from CAnyOgreMovableText, create the object
		void	_setupGeometry();
		void	_updateColors();

		/// 获取世界坐标系中的变换
		void	getWorldTransforms(Matrix4 *xform) const;

		/// 获取包围半径
		Real	getBoundingRadius(void) const {return mRadius;};

		/// 获取摄像机的视深
		Real	getSquaredViewDepth(const Camera *cam) const {return 0;};

		/// 获取世界坐标系中的朝向
		/// @note 一直面朝摄像机
		const   Quaternion&			getWorldOrientation(void) const;

		/// 获取在世界坐标系中的坐标
		const   Vector3&			getWorldPosition(void) const;

		/// 获取包围盒
		const   AxisAlignedBox&		getBoundingBox(void) const {return mAABB;};

		/// 获取标识名
		const   String&				getName(void) const {return mName;};

		/// 获取类型名
		const   String&				getMovableType(void) const {static Ogre::String movType = "CAnyOgreMovableText"; return movType;};

		void    _notifyCurrentCamera(Camera *cam);
		void    _updateRenderQueue(RenderQueue* queue);

		// from renderable
		void    getRenderOperation(RenderOperation &op);
		const   MaterialPtr&	getMaterial(void) const {assert(!mpMaterial.isNull());return mpMaterial;};
		const   LightList&		getLights(void) const {return mLList;};
	};
}
#endif
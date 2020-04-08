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
		/// ˮƽ���뷽ʽ
		enum HorizontalAlignment
		{
			H_LEFT,		///< �����
			H_CENTER,	///< ����
			H_RIGHT		///< �Ҷ���
		};

		/// ��ֱ���뷽ʽ
		enum VerticalAlignment
		{
			V_BELOW,///< �Ͷ˶���
			V_ABOVE,///< ���˶���
			V_CENTER///< ����
		};

	public:
		String				mFontName;///<
		String				mType;///<
		String				mName;///<
		DisplayString		mCaption;///< 
		HorizontalAlignment	mHorizontalAlignment;///< ˮƽ���뷽ʽ
		VerticalAlignment	mVerticalAlignment;///< ��ֱ���뷽ʽ

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
		Real				mRadius;///< ��Χ�뾶
		Real				mAdditionalHeight;///<

		Camera*				mpCam;///< �����ָ��
		RenderWindow*		mpWin;///< ��Ⱦ����ָ��
		Ogre::FontPtr				mpFont;///< ����ָ��
		MaterialPtr			mpMaterial;///< 
		MaterialPtr			mpBackgroundMaterial;///< ��������

		Vector3				mPositionOffset;///< 
		Vector3				mScaleOffset;///<

	public:
		/// ���캯��
		/// @param[in] name ��ʶ��
		/// @param[in] caption ��Ļ�ַ���
		/// @param[in] fontName ������
		/// @param[in] charHeight �ַ��߶�
		/// @param[in] colour �ַ���ɫ
		CAnyOgreMovableText(const Ogre::String& name,
			const Ogre::DisplayString& caption,
			const Ogre::String& fontName = "MyFont",
			Ogre::Real charHeight = 1.0f,
			Ogre::Real spaceWidth = 0.0f,
			const Ogre::ColourValue& colour = Ogre::ColourValue::White);

		virtual ~CAnyOgreMovableText(void);

		/// ����������
		void    setFontName(const String &fontName);

		/// ������ʾ��Ļ
		void    setCaption(const DisplayString &caption);

		/// ����������ɫ
		void    setColor(const ColourValue &color);

		/// �������ָ߶�
		void    setCharacterHeight(Real height);

		/// ���ü������
		void    setSpaceWidth(Real width);

		/// �������ֶ��뷽ʽ
		void    setTextAlignment(const HorizontalAlignment& horizontalAlignment,
			const VerticalAlignment& verticalAlignment);

		/// ����
		void    setAdditionalHeight( Real height );

		/// �Ƿ���ǰ����ʾ
		void    showOnTop(bool show=true);

		/// 
		void setPositionOffset(const Ogre::Vector3& offset);

		/// 
		Ogre::Vector3 getPositionOffset() const { return mPositionOffset; }

		/// 
		void setScaleOffset(const Ogre::Vector3& offset);

		/// 
		Ogre::Vector3 getScaleOffset() const { return mScaleOffset; }

		/// ��ȡ������
		const   String&			getFontName() const {return mFontName;}

		/// ��ȡ��Ļ�ַ���
		const   DisplayString&	getCaption() const {return mCaption;}

		/// ��ȡ������ɫ
		const   ColourValue&	getColor() const {return mColor;}

		/// ��ȡ�ַ��߶�
		Real    getCharacterHeight() const {return mCharHeight;}

		/// ��ȡ�������
		Real    getSpaceWidth() const {return mSpaceWidth;}

		/// 
		Real    getAdditionalHeight() const {return mAdditionalHeight;}

		/// ��ȡ�Ƿ�����ǰ����ʾ
		bool    getShowOnTop() const {return mOnTop;}

		/// ��ȡ��Χ��
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

		/// ��ȡ��������ϵ�еı任
		void	getWorldTransforms(Matrix4 *xform) const;

		/// ��ȡ��Χ�뾶
		Real	getBoundingRadius(void) const {return mRadius;};

		/// ��ȡ�����������
		Real	getSquaredViewDepth(const Camera *cam) const {return 0;};

		/// ��ȡ��������ϵ�еĳ���
		/// @note һֱ�泯�����
		const   Quaternion&			getWorldOrientation(void) const;

		/// ��ȡ����������ϵ�е�����
		const   Vector3&			getWorldPosition(void) const;

		/// ��ȡ��Χ��
		const   AxisAlignedBox&		getBoundingBox(void) const {return mAABB;};

		/// ��ȡ��ʶ��
		const   String&				getName(void) const {return mName;};

		/// ��ȡ������
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
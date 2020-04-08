#ifndef __BITVECTOR_H__D40A115A_BC2F_4125_A068_D151EFFA2677
#define __BITVECTOR_H__D40A115A_BC2F_4125_A068_D151EFFA2677

#include <vector>

class CBitVector
{
	typedef unsigned long BASEUNIT;

	typedef std::vector<BASEUNIT> BASEUNITVECTOR;

	BASEUNITVECTOR	m_vecBaseUnits;

	enum { BitsPerUnit = sizeof(BASEUNIT) * 8 };

public:
	CBitVector(){}	

	~CBitVector(){}

	template<typename T>
	CBitVector(const T& that)
	{
		*this = that;
	}

	inline CBitVector& operator=(const CBitVector& that)
	{
		this->m_vecBaseUnits = that.m_vecBaseUnits ;
		return *this;
	}

	inline bool IsBitSet(const int nBitIndex) const
	{
		return nBitIndex >=0 && 
			nBitIndex < BitsPerUnit *(int)this->m_vecBaseUnits.size() && 
			(this->m_vecBaseUnits[nBitIndex/BitsPerUnit] & ((BASEUNIT)1 << (nBitIndex % BitsPerUnit)));
	}

	inline bool operator[](int nBitIndex) const
	{
		return (this->m_vecBaseUnits[nBitIndex/BitsPerUnit] & ((BASEUNIT)1 << (nBitIndex % BitsPerUnit)));
	}

	inline CBitVector operator+(int nBitIndex) const		//Returns a BitVector with the Given BitIndex set to True along with existing ones
	{
		CBitVector tempVector(*this);
		return tempVector += nBitIndex;
	}

	inline CBitVector& operator+=(int nBitIndex)				//Modifies the BitVector by setting the Given BitIndex to True
	{
        while(nBitIndex >= BitsPerUnit * (int)this->m_vecBaseUnits.size())
			this->m_vecBaseUnits.push_back(0);

		this->m_vecBaseUnits[nBitIndex/BitsPerUnit] |= ((BASEUNIT)1 << (nBitIndex % BitsPerUnit));
		return *this;
	}

	inline CBitVector operator-(int nBitIndex) const		//Returns a BitVector with the Given BitIndex set to False along with existing ones
	{
		CBitVector tempVector(*this);
		return tempVector -= nBitIndex;
	}

	inline CBitVector& operator-=(int nBitIndex)				//Modifies the BitVector by setting the Given BitIndex to False
	{
        while(nBitIndex >= BitsPerUnit * (int)this->m_vecBaseUnits.size())
			this->m_vecBaseUnits.push_back(0);

		this->m_vecBaseUnits[nBitIndex/BitsPerUnit] &= ~(((BASEUNIT)1 << (nBitIndex % BitsPerUnit)));
		return *this;
	}

	inline int GetFirstTrueIndex()	const						//Returns the First Index Whose Bit Value is Set to True; else returns -1 if none found
	{
		return GetNextIndex(-1, true);
	}

	inline int GetNextTrueIndex(int nCurrentIndex)	const		//Returns any Index after nCurrentIndex Whose Bit Value is Set to True; else returns -1 if none found
	{
		return GetNextIndex(nCurrentIndex, true);
	}

	inline int GetFirstFalseIndex()	const
	{
		return GetNextIndex(-1, false);
	}

	inline int GetNextFalseIndex(int nCurrentIndex)	const
	{
		return GetNextIndex(nCurrentIndex, false);
	}

	inline CBitVector operator|(const CBitVector& that) const
	{
		CBitVector tempVector(*this);
		return tempVector |= that;
	}

	CBitVector& operator|=(const CBitVector& that)
	{
		while(m_vecBaseUnits.size() < that.m_vecBaseUnits.size())			//Add Space for any Extra Units
			m_vecBaseUnits.push_back(0);

		BASEUNITVECTOR::const_iterator iterBegin = that.m_vecBaseUnits.begin();
		BASEUNITVECTOR::const_iterator iterEnd = that.m_vecBaseUnits.end();
		BASEUNITVECTOR::const_iterator iter = iterBegin;

		for(int nBaseUnitIndex=0 ; iter != iterEnd; ++iter, ++nBaseUnitIndex)		
			m_vecBaseUnits[nBaseUnitIndex] |= *iter;

		return *this;
	}

	inline CBitVector operator&(const CBitVector& that) const
	{
		CBitVector tempVector(*this);
		return tempVector &= that;
	}

	CBitVector& operator&=(const CBitVector& that)
	{
		while(m_vecBaseUnits.size() > that.m_vecBaseUnits.size())			//Remove any Extra Units we have
			m_vecBaseUnits.pop_back();

		BASEUNITVECTOR::iterator iterBegin = m_vecBaseUnits.begin();
		BASEUNITVECTOR::iterator iterEnd = m_vecBaseUnits.end();
		BASEUNITVECTOR::iterator iter = iterBegin;

		for(int nBaseUnitIndex=0 ; iter != iterEnd; ++iter, ++nBaseUnitIndex)		
			*iter &= that.m_vecBaseUnits[nBaseUnitIndex];

		return *this;
	}

	inline bool Any() const							//Returns True if Any bit is Set to True
	{
		for(int i=0, nMax = (int) this->m_vecBaseUnits.size(); i < nMax; ++i)
			if(this->m_vecBaseUnits[i])	
				return true;
		return false;
	}

	inline bool None() const
	{
		return !Any();
	}

	inline void Clear()
	{
		for(int i=0, nMax = (int) this->m_vecBaseUnits.size(); i < nMax; ++i)
			this->m_vecBaseUnits[i] = 0;
	}

	inline int BitCount() const	// Returns the number of bits set
	{
		BASEUNITVECTOR::const_iterator iter = m_vecBaseUnits.begin();
		BASEUNITVECTOR::const_iterator iterEnd = m_vecBaseUnits.end();

		int nBitCount = 0;

		for(int nBaseUnitIndex=0 ; iter != iterEnd; ++iter, ++nBaseUnitIndex)
		{
			BASEUNIT nUnit = m_vecBaseUnits[nBaseUnitIndex];	//TODO: Improve performance using char lookup for bitcount
			while(nUnit)
			{
				if(nUnit & 1)	// if bit set
					nBitCount ++;
				nUnit = nUnit >> 1;
			}
		}

		return nBitCount;
	}

	inline bool operator==(const CBitVector& other) const
	{
		int nMyTrueIndex =  GetFirstTrueIndex();
		int nOtherTrueIndex = other.GetFirstTrueIndex();

		while((nMyTrueIndex == nOtherTrueIndex) && (nMyTrueIndex!=-1) && (nOtherTrueIndex!=-1))
		{
			nMyTrueIndex = GetNextTrueIndex(nMyTrueIndex);
			nOtherTrueIndex = other.GetNextTrueIndex(nOtherTrueIndex);
		}
		
		return nMyTrueIndex == nOtherTrueIndex;
	}

	inline bool operator!=(const CBitVector& other) const
	{
		return !(*this == other);
	}

protected:
	int GetNextIndex(int nCurrentIndex, bool bVal) const
	{
		++nCurrentIndex;		//Run Past the Current Index (Start Searching From Next Index Onwards)

		if(nCurrentIndex <0 || nCurrentIndex >= BitsPerUnit * (int) m_vecBaseUnits.size())	return -1;

		unsigned int nBaseUnitIndex  = (nCurrentIndex / BitsPerUnit);
		unsigned int nBaseUnitOffset = (nCurrentIndex % BitsPerUnit);	

		//BASEUNITVECTOR::const_iterator iterBegin = m_vecBaseUnits.begin();
		BASEUNITVECTOR::const_iterator iterEnd = m_vecBaseUnits.end();
		BASEUNITVECTOR::const_iterator iter = m_vecBaseUnits.begin() + nBaseUnitIndex;

		for( ;iter != iterEnd; ++iter, ++nBaseUnitIndex, nBaseUnitOffset = 0)
		{
			BASEUNIT nVal = *iter;

			unsigned int nOffset =  nBaseUnitOffset;	

			nVal >>= nOffset;

			while(nVal)
			{
				if((nVal & 1) == bVal)
					return nBaseUnitIndex * BitsPerUnit + nOffset;
				nVal >>= 1;
				nOffset++;
			}
		}

		return -1;	
	}
};

#endif

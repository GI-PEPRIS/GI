/*!
 * The AnyVis of PetroCOVERY Solution is a collection of native C++ classes that implement 
 * kinds of information visualization etc.
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
#ifndef ANYWAY_RCF_CORE_TAG_CAST_H
#define ANYWAY_RCF_CORE_TAG_CAST_H


#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_base_of.hpp>

namespace anyway { namespace rcf
{

template
<
    typename Tag,
    typename BaseTag,
    typename BaseTag2 = void,
    typename BaseTag3 = void,
    typename BaseTag4 = void,
    typename BaseTag5 = void,
    typename BaseTag6 = void,
    typename BaseTag7 = void
>
struct tag_cast
{
    typedef typename boost::mpl::if_
        <
          typename boost::is_base_of<BaseTag, Tag>::type,
          BaseTag,
          // Try next one in line:
          typename tag_cast
            <
                Tag, BaseTag2, BaseTag3, BaseTag4,
                BaseTag5, BaseTag6, BaseTag7, void
            >::type
        >::type type;
};

// Specialization for last one
template <typename Tag>
struct tag_cast<Tag, void, void, void, void, void, void, void>
{
    // If not found, take specified tag, so do not cast
    typedef Tag type;
};

#endif // DOXYGEN_NO_SPECIALIZATIONS


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_CORE_TAG_CAST_HPP

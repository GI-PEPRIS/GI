#ifndef ANYWAY_RCF_DIMENSION_STRATEGY_CHUNK_WRITE_WITH_NAMEDPIPE_H
#define ANYWAY_RCF_DIMENSION_STRATEGY_CHUNK_WRITE_WITH_NAMEDPIPE_H


namespace anyway 
{
	namespace rcf
	{
		struct chunk_write_with_namedpipe
		{
			template
			<
				typename Servant,
				typename ChunkFile
			>
			static inline void apply(Servant const& servant, ChunkFile const& chunkfile)
			{
			}
		};
	}

} // namespace 

#endif
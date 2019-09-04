
#ifndef _USER_TYPE_H
#define _USER_TYPE_H

template <class T> class GREGISTER
{
	public:
		GREGISTER (void)
		{
			m_in = 0;
			m_out = 0;
		}			
		
		void operator = (T p_data)
		{
			m_in = p_data;
		}

		void operator = (GREGISTER p_reg)
		{
			m_in = p_reg.m_out;
		}

		void operator += (T p_data)
		{
			m_in = m_out + p_data;
		}

		void operator -= (T p_data)
		{
			m_in = m_out - p_data;
		}

		void operator *= (T p_data)
		{
			m_in = m_out * p_data;
		}

		void operator /= (T p_data)
		{
			m_in = m_out / p_data;
		}

		void operator %= (T p_data)
		{
			m_in = m_out % p_data;
		}

		void operator &= (T p_data)
		{
			m_in = m_out & p_data;
		}

		void operator |= (T p_data)
		{
			m_in = m_out | p_data;
		}

		void operator ^= (T p_data)
		{
			m_in = m_out ^ p_data;
		}

		void operator <<= (T p_data)
		{
			m_in = m_out << p_data;
		}

		void operator >>= (T p_data)
		{
			m_in = m_out >> p_data;
		}

		T operator ++ (int)   // post inc
		{
			m_in = m_out + 1;
			return (m_out);
		}

		T operator -- (int)  // post dec
		{
			m_in = m_out - 1;
			return (m_out);
		}

		T operator ++ ()    // pre inc
		{
			m_in = m_out + 1;
			return (m_in);
		}

		T operator -- ()    // pre dec
		{
			m_in = m_out - 1;
			return (m_in);
		}

		bool operator == (GREGISTER p_reg)
		{
			return (m_out == p_reg.m_out);
		}

		bool operator == (T p_data)
		{
			return (m_out == p_data);
		}

		bool operator != (GREGISTER p_reg)
		{
			return (m_out != p_reg.m_out);
		}

		bool operator != (T p_data)
		{
			return (m_out != p_data);
		}		

		bool operator < (GREGISTER p_reg)
		{
			return (m_out < p_reg.m_out);
		}

		bool operator < (T p_data)
		{
			return (m_out < p_data);
		}		

		bool operator <= (GREGISTER p_reg)
		{
			return (m_out <= p_reg.m_out);
		}

		bool operator <= (T p_data)
		{
			return (m_out <= p_data);
		}


		bool operator > (GREGISTER p_reg)
		{
			return (m_out > p_reg.m_out);
		}

		bool operator > (T p_data)
		{
			return (m_out > p_data);
		}		

		bool operator >= (GREGISTER p_reg)
		{
			return (m_out >= p_reg.m_out);
		}

		bool operator >= (T p_data)
		{
			return (m_out >= p_data);
		}

		bool operator ! ()
		{
			return ( !m_out );
		}
		
		
		operator T() {return m_out;}

		void shift(void)
		{
			m_out = m_in;
		}

		void SetValue(T p_data)
		{
			m_in = p_data;
			m_out = p_data;
		}

		void GetInput(T *p_pdata)
		{
			*p_pdata = m_in;
		}
		
	private:
		T m_in, m_out;
};

/*
typedef union REGFS_WORD
{
	DSPU32 u32Value;
	struct  SPLIT_VALUE
	{
		DSPU32      u1TSrcPageIdx: 1;
		DSPU32      u1TDestPageIdx: 1;

		DSPU32      u1ZSrcPageIdx: 1;
		DSPU32      u1ZDestPageIdx: 1;

		DSPU32      u1YSrcPageIdx: 1;
		DSPU32      u1YDestPageIdx: 1;

		DSPU32      u1XSrcPageIdx: 1;
		DSPU32      u1XDestPageIdx: 1;

		DSPU32      u24Rev: 24;
	} details;
} REGFS_WORD;

*/
#endif



